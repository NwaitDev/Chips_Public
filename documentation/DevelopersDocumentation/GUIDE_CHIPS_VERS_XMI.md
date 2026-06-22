# Guide de génération CHIPS → XMI


## XMI generation options

The CLI supports choosing the XMI schema version with `--schema-version`.
Valid values are `1.1` and `2`. The default is `1.1`.

Examples:

```bash
./chipsc path/to/file.chips --schema-version 1.1
./chipsc path/to/file.chips --schema-version 2
```


## 1) Objectif du module

Ce dossier implémente la conversion d'un AST CHIPS vers un fichier XMI conforme au méta-modèle CHIPS (`chips1.1.ecore` ou `chips2.ecore`).

Le flux réel aujourd'hui est :

1. parsing du fichier `.chips` ;
2. construction de l'AST ;
3. visite de l'AST pour produire le **corps XMI** et collecter les namespaces ;
4. écriture finale du fichier XMI (header + corps + footer).

Le but est de produire des chemins stables (`//@...`) pour référencer les éléments entre eux et générer les bons `xsi:type`.

---

## 2) Vue d'ensemble du pipeline (de `.chips` à `.xmi`)

### 2.1 Point d'entrée

Le pipeline est orchestré dans `ChipsDriver.cpp` :

- `driver::parse(...)`
  - lance le parser,
  - puis appelle `generate_xmi(...)` si parsing OK et génération activée.

- `driver::generate_xmi(output_file, source_filename)`
  - crée un `ChipsToXmiWriter body_writer` + `ChipsToXmiVisitor visitor` sur un `std::ostringstream body_out`,
  - appelle `ast->accept(visitor)` pour générer le corps XMI,
  - bloque si erreurs sémantiques (`visitor.has_semantic_errors()`),
  - crée un `ChipsToXmiWriter writer` final,
  - copie les namespaces collectés depuis `body_writer` (`copy_namespaces_from`),
  - écrit `xmi_header(...)`, puis le corps bufferisé, puis `xmi_footer()`.

### 2.2 Pourquoi 2 writers ?

- **Writer 1 (`body_writer`)** : utilisé pendant la visite pour enregistrer dynamiquement les namespaces réellement utilisés.
- **Writer 2 (`writer` final)** : écrit le fichier de sortie final avec un header complet et cohérent.

Cette stratégie évite d'écrire le header avant de connaître tous les namespaces.

---

## 3) Rôle de chaque composant

## 3.1 `ChipsToXmiVisitor`

Responsabilités principales :

- parcourir l'AST (pattern Visitor),
- générer le XML de chaque nœud (définitions, statements, expressions),
- maintenir le chemin AST/XMI courant (`m_current_ast_path`),
- enregistrer les symboles/références (`m_symbol_table`),
- enrichir la table des définitions (`m_definitions_table`) pour les `having` mappings,
- signaler les erreurs sémantiques (symboles manquants, doublons),
- déclarer les namespaces via `ensure_namespace_for_prefix` / `ensure_namespace_for_type`.

## 3.2 `ChipsToXmiWriter`

Responsabilités principales :

- générer le header/footer XMI,
- maintenir l'ensemble des namespaces utilisés,
- construire `xsi:schemaLocation` dynamiquement,
- fournir une conversion « writer direct » (`chips_to_xmi`) qui existe encore mais reste plus basique que le visitor.

> Important : dans le flux principal actuel, c'est le **visitor** qui fait la génération détaillée du corps XMI.

---

## 4) Logique de génération détaillée

## 4.1 Gestion des chemins (`m_current_ast_path`)

Le visitor manipule un chemin de type EMF (`//@...`) pour localiser chaque élément.

Exemples :

- préambule n°0 : `//@preamble/@definitions.0`
- système statement n°2 : `//@system/@system.2`
- variable d'un statement : `.../@variable`

Méthodes clés :

- `push_ast_path(segment)` : descend dans l'arbre,
- `pop_ast_path(segment)` : remonte,
- `set_ast_path(path)` : override ponctuel (utile pour insérer un statement supplémentaire).

Ce chemin est ensuite enregistré dans la table des symboles pour résoudre les références `variable="..."`.

## 4.2 Table des symboles

`m_symbol_table : map<string, SymbolInfo>` relie un nom logique à :

- `path` (chemin XMI absolu),
- `type` (ex. `physical`, `logical_parameter:int`, `channel`, `actuator:bool`, etc.).

Utilisation :

- `register_variable(...)` lors des déclarations,
- `get_symbol_info(...)` / `get_ast_path_by_name(...)` lors des références.

Comportements importants :

- détection de doublon dans `register_variable` (erreur sémantique),
- fallback case-insensitive dans `get_ast_path_by_name`,
- fallback permissif (retour du nom) si symbole introuvable.

## 4.3 Déclarations + assignment implicite

Pour certains nœuds (`dataflow_full_declaration_node`, `collective_dataflow_full_declaration_node`), si une RHS existe :

- le visitor génère **2 statements** :
  1) déclaration,
  2) assignment.

Le compteur `m_extra_statements_generated` sert à corriger l'indexation des chemins `@statements.N` quand un statement source produit plusieurs statements XMI.

## 4.4 Dispatch des statements système

`visit(s_statement_node&)` redirige selon `get_statement_type()` vers :

- `implements_node`,
- `link_node`,
- `plugging_node`,
- `s_loop_node`,
- `s_if_node`,
- `s_if_else_node`,
- `functionnal_block_instanciation_node`.

## 4.5 Cas spéciaux de génération

- `implements_node`
  - génère `implements_statement` avec l'attribut **`implmentation`** (typo volontaire de schéma, conservée pour compatibilité).

- `plugging_node`
  - distingue 3 cas :
    1) `channel_plugging`,
    2) `feeding_logical_*`,
    3) `feeding_physical_*`.
  - choisit les types via les infos de symboles (`channel`, `logical_parameter:*`, `sensor:*`, `actuator:*`).

- `node_mappings_node`
  - génère `having_statements` dans les `implementation_definition`;
  - mappe `channel_aliasing` vs `contextual_aliasing` selon le type de variable.

---

## 5) Structures, enum et membres importants

## 5.1 Dans `ChipsToXmiVisitor`

### Enum `StatementFamily`

Valeurs :

- `Auto`, `Primitive`, `System`, `Node`, `Collective`, `Implementation`.

But : déterminer le préfixe `chips.statements.*` selon le contexte (`/@system`, `/@with`, `/@operations`, etc.).

### Struct `SymbolInfo`

Champs :

- `path` : chemin XMI,
- `type` : type métier (ex. `channel`, `contextual`, `physical`, `logical_parameter:bool`, ...).

But : typer et localiser un symbole pour écrire les bons `xsi:type` et attributs `variable`.

### Struct `DefinitionInfo`

Champs :

- `name`, `type`, `path`, `index`,
- `variables` : symboles locaux de la définition (with/init/then).

But : résoudre les mappings d'implémentation (`having`) dans le bon scope de définition.

### Membres d'état clés

- `m_current_ast_path` : position courante,
- `m_symbol_table` : symboles globaux,
- `m_definitions_table` : définitions + variables internes,
- `m_current_definition` : contexte de définition en cours,
- `m_impl_def_implementing_node` / `m_impl_def_implemented_object` : contexte temporaire pour `node_mappings_node`,
- `m_statement_tag` : override de nom de tag (`system`, `if_statements`, `else_statements`, ...),
- `m_semantic_errors` : accumulation d'erreurs,
- `m_extra_statements_generated` : compensation d'index.

## 5.2 Dans `ChipsToXmiWriter`

### Membres clés

- `m_namespace_urls` : map `prefix -> URL`,
- `m_used_namespaces` : set des préfixes utilisés,
- `m_nodeToId` / `m_idCounter` : génération d'IDs internes,
- `m_schemaVersion` : choix `chips2.ecore` vs `chips1.1.ecore`.

---

## 6) Fonctions helpers (explication explicite)

## 6.1 Helpers du visitor

- `detect_statement_family()`
  - infère la famille via `m_current_ast_path`.

- `statement_prefix(family)`
  - mappe une famille vers `chips.statements.<...>`.

- `statement_type(suffix, family)`
  - compose `statement_prefix + ':' + suffix`.

- `writeAttribute(name, value)`
  - écrit un attribut XML,
  - si `xsi:type`, déclenche `ensure_namespace_for_type(value)`.

- `ensure_namespace_for_prefix(ns_prefix)`
  - convertit `chips.a.b` en URL `http://chips/a/b` et l'enregistre côté writer.

- `ensure_namespace_for_type(type_value)`
  - extrait le préfixe avant `:` et appelle `ensure_namespace_for_prefix`.

- `endEmptyElement()`
  - utilitaire de fermeture courte (` />`).

- `getExpressionValue(expression_node&)`
  - extrait une représentation string d'une expression (littéral, identifiant, appel, ...).

- `write_collective_rvalue(...)`
  - sérialise les rvalues en contexte collectif (littéraux, variables, opérateurs, keywords `input/stop`).

- `write_collective_output_expression(...)`
  - sérialise les expressions d'output collectif.

- `write_index_from_suffixes(...)`
  - convertit les suffixes d'indexation (`[...]`) en nœuds `<index ...>`.

- `get_ast_path_by_name(name)`
  - résout un nom vers chemin XMI (avec fallback case-insensitive + erreur sémantique si introuvable).

- `get_xsi_type_for_symbol(SymbolInfo)`
  - mappe type symbole (`physical/logical/object`) vers type d'expression système.

- `get_declaration_type_from_definition(definition_type)`
  - mappe type de définition vers type de déclaration système.

- `get_symbol_info(name)`
  - lookup simple dans la table des symboles.

- `report_semantic_error(message)`
  - stocke + logge l'erreur (avec contexte de path).

## 6.2 Helpers du writer

- `xmi_header(filename)`
  - écrit prologue XML,
  - injecte namespaces dynamiques triés,
  - construit `xsi:schemaLocation`.

- `xmi_footer()`
  - ferme `</chips:program>`.

- `add_namespace_if_needed(prefix, url)`
  - enregistre un namespace une seule fois.

- `collect_namespaces(root)` + sous-fonctions
  - pré-collecte statique par inspection AST (partielle).

- `copy_namespaces_from(other)`
  - transfère les namespaces collectés entre writers.

- `nodeId(node)` / `nextId(prefix)`
  - IDs stables par instance de nœud.

---

## 7) TODO restants (explicites)

## 7.1 TODO de complétude fonctionnelle (visitor)

Ces méthodes existent mais génèrent seulement un commentaire placeholder :

- contexte déclaratif/primitif :
  - `visit(c_signature_node)`
  - `visit(with_statement_node)`
  - `visit(statements_node)`
  - `visit(rhs_assignment_node)`
  - `visit(assignment_node)`
  - `visit(this_attribute_node)`
  - `visit(function_call_statement_node)`
  - `visit(if_node)`
  - `visit(loop_node)`
  - `visit(block_node)`

- expressions :
  - `visit(expression_node)`
  - `visit(suffixable_node)`
  - `visit(unary_expression_node)`
  - `visit(number_literal_node)`
  - `visit(function_call_node)`
  - `visit(plugging_expr_node)`
  - `visit(collective_cast_node)`
  - `visit(collective_operation_node)`
  - `visit(object_virtual_output_node)`
  - `visit(object_physical_attribute_node)`
  - `visit(cast_node)`
  - `visit(stop_node)`
  - `visit(input_node)`
  - `visit(c_cast_node)`
  - `visit(context_expression_node)`
  - `visit(integrated_function_node)`
  - `visit(context_decl_node)`
  - `visit(suffixes_node)`
  - `visit(paren_expression_node)`

- collectif/configuration :
  - `visit(c_keywords_node)`
  - `visit(spread_node)`
  - `visit(collect_node)`
  - `visit(c_statements_node)`
  - `visit(c_statement_node)`
  - `visit(c_loop_node)`
  - `visit(c_if_node)`
  - `visit(c_expressions_node)`
  - `visit(collective_dataflow_defaulted_decls_node)`
  - `visit(collective_dataflow_defaulted_decl_node)`
  - `visit(collective_rhs_assignment_node)`

- dataflow types/params :
  - `visit(dataflow_type_node)`
  - `visit(physical_dataflow_parameter_type_node)`
  - `visit(expressions_node)`
  - `visit(dataflow_parameter_list_node)`
  - `visit(physical_dataflow_parameter_list_node)`
  - `visit(dataflow_parameter_decls_node)`
  - `visit(physical_dataflow_parameter_decls_node)`
  - `visit(dataflow_parameter_decl_node)`
  - `visit(physical_dataflow_parameter_decl_node)`

## 7.2 TODO métier identifiés dans code existant

- `physical_function_definition_node` : distinguer proprement sensor vs actuator (commentaire TODO, aujourd'hui heuristique de type).
- `ChipsToXmiWriter::collect_namespaces_from_preamble` : enrichir la collecte de namespaces selon contenu réel.

## 7.3 TODO du writer « direct »

`ChipsToXmiWriter::preamble_to_xmi` contient encore des placeholders :

- object: with section,
- physical: with/init/then/outputs,
- logical: init/then/outputs,
- implementation: implemented_object/implementing_node/having.

Ce point est moins bloquant si le visitor reste le chemin principal.
