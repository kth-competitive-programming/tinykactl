(setq kactl-ext "cc")
(defun c-lite-compile () (interactive)
  (shell-command (concat "g++ -ansi -lm -O2 -pedantic -Wall -o "
			 (file-name-sans-extension buffer-file-name) " "
			 buffer-file-name)))

(defun c-lite-new-file (name) (interactive "FCFF: ") 
  (find-file name) (and (not (file-exists-p name))
			(string-equal (file-name-extension name) kactl-ext)
			(insert-file "Template.cpp"))
  (indent-buffer)
  (replace-string "%P" (file-name-nondirectory (file-name-sans-extension name))
		  nil (point-min) (point-max)))

(defun c-lite-test () (interactive) 
  (let ((name (file-name-sans-extension buffer-file-name)))
    (shell-command (concat name " < " name ".in"))))

(defun c-lite-send () (interactive)
  (and (string-equal (file-name-extension buffer-file-name) kactl-ext)
       (y-or-n-p "Send? ") (shell-command (concat "submit " buffer-file-name))))

(global-set-key "\C-x\C-f" 'c-lite-new-file)
(global-set-key "\C-cc" 'c-lite-compile)
(global-set-key "\C-ct" 'c-lite-test)
(global-set-key "\C-cs" 'c-lite-send)
