(defun kactl-print () (interactive)
  (shell-command (concat "a2ps --line-numbers=1 " 
			 buffer-file-name) " &"))

(defun kactl-diff () (interactive)
  (let ((N (file-name-sans-extension buffer-file-name)))
    (shell-command 
     (concat N " < " N ".in > " N 
	     ".temp && diff " N ".out " N ".temp &"))))

(global-set-key "\C-cp" 'kactl-print)
(global-set-key "\C-cd" 'kactl-diff)
(global-set-key "\C-cg" 'goto-line)

remove Lock = Caps_Lock
keycode 0x40 = less greater bar

remove Mod4 = Meta_R
keycode 0xEE = Mode_switch
add Mod2 = Mode_switch
