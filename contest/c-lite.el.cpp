(setq kactl-ext "cc")
(defun c-lite-compile () (interactive)
  (shell-command (concat "g++ -ansi -lm -O2 -pedantic -Wall -o "
			 (file-name-sans-extension buffer-file-name) " "
			 buffer-file-name)))

(defun c-lite-new-file (N) (interactive "FCFF: ") 
  (find-file N) (or (file-exists-p N)
		    (not (string-equal (file-name-extension N) kactl-ext))
		    (insert-file "Template.cpp")))

(defun c-lite-test () (interactive) 
  (let ((N (file-name-sans-extension buffer-file-name)))
    (shell-command (concat N " < " N ".in"))))
;;(shell-command (file-name-sans-extension buffer-file-name)))

(defun c-lite-send () (interactive)
  (and (string-equal (file-name-extension buffer-file-name) kactl-ext)
       (y-or-n-p "Send? ") (shell-command (concat "submit " buffer-file-name))))

(global-set-key "\C-x\C-f" 'c-lite-new-file)
(global-set-key "\C-cc" 'c-lite-compile)
(global-set-key "\C-ct" 'c-lite-test)
(global-set-key "\C-cs" 'c-lite-send)