
# Contributing Guidelines

These are pretty common reminders, but I guess it's important to write them down here anyway: Keep changes small, one stage at a time, and run the full pipeline on at least one example before opening a pull request.

- **Bash** (`chipsc`, `chipsc_lib/`): `set -euo pipefail` everywhere, every tool call through `run_step`, option checks through `require_format`.
- **C++**: C++17, one `visit*` / `translate*` per grammar label, errors via `semantic_fail` / `fail` with the source position.
- **Metamodels**: a change to an `.ecore` file is a breaking change for the XMI writer and the ATL rules; change all three in the same pull request.
- **Versioning**: the version is printed by `chipsc -i` (currently v1.0.0, October 2026); bump it there with each release.

## Contribution Policy

I will write here two sub-sections according to whether I am still doing my PhD thesis (which should end in october 2027, hopefuly) or not.

### Before October 2027

Anyone can pull and fork any branch of the repository, but I will only accept as contributors the people with who the scientific interest of a contribution to the language has been validated with my supervisors and I. Until the time I write this, only students working with us during one of their Master 2 degree project or internship have been integrated to the Github contributors.

If you already developped your own fork of the repository and believe it could be useful to integrate your work to the official Chips language, get in touch with me!

### After October 2027

I have no concrete idea on how open source repositories are managed. But yeah, that's the idea. Let's do that. But for sure, this language will be OPEN SOURCE and COMMUNITY MANAGED.