" used for backward search in current zathura-neovim setup
" place in or add to ftplugin/tex.vim
" zMzv and zv will open fold at the curser, but close all others
if !exists('*Synctex_backward')
	function Synctex_backward(file, line)
		update
		exec 'edit +' . a:line . ' ' . a:file
		normal! zMzv
	endfunction
endif
