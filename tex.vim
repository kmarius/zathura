" used for backward search in current zathura-neovim setup
" place in or add to ftplugin/tex.vim
" GzMzv and zv will open folds
if !exists('*Synctex_backward')
	function! Synctex_backward(file, line)
		let file_sub = substitute(a:file, '/./', '/', 'g')
		if file_sub == expand('%:p')
			exec 'normal! ' . a:line . 'GzMzv'
		else
			write
			exec 'edit +' . a:line . ' ' . a:file
			normal! zv
		endif
	endfunction
endif
