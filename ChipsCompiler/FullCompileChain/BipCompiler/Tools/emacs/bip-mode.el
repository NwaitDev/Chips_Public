;;; bip-mode.el --- major mode for editing BIP code

;; Copyright (C) 2007 Olivier Constant

;; Created: 2007-05-10
;; Modified: 2012-04-06 by Benoit Boyer

;;; Changelog:
;; The keyword list is now compatible with the new BIP syntax.
;; The comments font locking works correctly with Emacs. The previous
;; entry that was apparently designed for XEmacs is not supported anymore.

;;; Todo:
;; RegExp are particular simple. Some advanced rules would be
;; welcommed to fontify correctly type and annotation identifiers.
;; It would also be nice to have implement indentation...


(defconst bip-version "0.2" "BIP Mode version number.")

;;; License

;; This program is free software; you can redistribute it and/or
;; modify it under the terms of the GNU General Public License
;; as published by the Free Software Foundation; either version 2
;; of the License, or (at your option) any later version.

;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with this program; if not, write to the Free Software
;; Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

;;; Usage

;; Place the file in a folder you add to your load path list
;; (add-to-list 'load-path "~/emacs/lisp")
;; Rename this file to bip-mode.el if it isn't already then place it in
;; your Emacs lisp path (eg. site-lisp) and add to your .emacs file:
;;   (require 'bip-mode)
;; If you want colorization, turn on global-font-lock or
;; add this to your .emacs:
;;   (add-hook 'bip-mode-user-hook 'turn-on-font-lock)

;; To not increase the Emacs loading time, it is strongly recommended
;; to byte-compile the bip-mode.el file. Instead of loading the
;; bip-mode.el, Emacs will load directly the corresponding file
;; bip-model.elc.

;;; Commentary:


;;; Code:

;; (require 'font-lock)
;; (eval-when-compile
;; (require 'regexp-opt))

;; Note whether we're in XEmacs
(defconst xemacsp (string-match "Lucid\\|XEmacs" emacs-version)
  "Non nil if using XEmacs.")

;; Hook that can be changed by the user
(defvar bip-mode-hook nil)

;; File extension added to autoload list for BIP files
(add-to-list 'auto-mode-alist '("\\.bip\\'" . bip-mode))

;; Syntax table
;; Init to an empty table
(defvar bip-mode-syntax-table
  (let ((bip-mode-syntax-table (make-syntax-table)))
    (if xemacsp nil (progn
                      (modify-syntax-entry ?- ". 12b" bip-mode-syntax-table)
                      (modify-syntax-entry ?\n "> b"
                                           bip-mode-syntax-table) )) bip-mode-syntax-table)
  "Syntax table for bip-mode")

;; Keymap for BIP
(defvar bip-mode-map
  (let ((bip-mode-map (make-keymap)))
    (define-key bip-mode-map "\C-c\C-c" 'comment-region)
    bip-mode-map)
  "Keymap for BIP major mode")

;; BIP keywords
(defconst bip-keywords
  (eval-when-compile
    (regexp-opt
     '(
       "package"
       "extern"
       "port type"
       "export port"
       "define" "'"
       "connector" "component"
       "place" "initial to"
       "on" "from" "to" "provided" "up" "down"
       "end"
       )))
  "BIP keywords.")

;; BIP types
(defconst bip-types
  (eval-when-compile
    (regexp-opt
     '(
       "data type"
       "atom type"
       "connector type"
       "compound type"
       "bool" "int" "float"
       )))
  "BIP types.")

;; BIP functions
(defconst bip-functions
  (eval-when-compile
    (regexp-opt
     '(
       "{#"
       "#}"
       "false"
       "true"
       )))
  "BIP functions")

;; Set up font locking
(defconst bip-font-lock-keywords-1
  (list
   ;; Fontify keywords
   (cons
    (concat "\\<\\(" bip-keywords "\\)\\>")
    'font-lock-keyword-face)
   ;; Fontify types
   (cons
    (concat "\\<\\(" bip-types "\\)\\>")
    'font-lock-type-face)
   ;; Fontify functions
   (cons
    (concat "\\<\\(" bip-functions "\\)\\>")
    'font-lock-builtin-face)
   ;; This is not clear why the comment font locking was not originaly
   ;; specified for Emacs, but it seems really required for all tests
   ;; that I made...  So, I decided to define it by default: there are
   ;; two entries for the typical comments -- as in C-language --
   ;; supported by BIP:
   (list (concat "//.*$") 0 'font-lock-comment-face t)
   (list (concat "/\*.*\*/") 0 'font-lock-comment-face t)
   ;; The previous non-working definition for comments:
   ;; Add comments for XEmacs
   ;;(if xemacsp
   ;;    (list (concat "//.*$") 0 'font-lock-comment-face t)
   ;;  )
   )
  "First level of highlighting for BIP"
  )

(defvar bip-font-lock-keywords bip-font-lock-keywords-1
  "Default highlighting expressions for BIP mode.")

;; BIP mode initialisation
(defun bip-mode ()
  "Major mode for editing BIP code."

  (interactive)
  (kill-all-local-variables)
  (set-syntax-table bip-mode-syntax-table)
  (use-local-map bip-mode-map)

  ;; This is only useful for comment-region and not highlighting
  (make-local-variable 'comment-start)
  (setq comment-start "//")
  (make-local-variable 'comment-start-skip)
  (setq comment-start-skip "//+ *")

  (set (make-local-variable 'font-lock-defaults) '(bip-font-lock-keywords))

  (setq major-mode 'bip-mode)
  (setq mode-name "BIP")
  (run-hooks 'bip-mode-hook)
  (message "BIP Mode activated"))

(provide 'bip-mode)

;;; bip-mode.el ends here
