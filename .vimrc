set autoread

let working_path = getcwd()
let vimrc_path = expand('<sfile>:p:h')



map <F1> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh TCC debug)" <CR>
map <F2> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh GCC debug)" <CR>
map <F3> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh CLANG debug)" <CR>

map <F5> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh TCC release)" <CR>
map <F6> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh GCC release)" <CR>
map <F7> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh CLANG release)" <CR>

map <C-0> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh CLANG debug) && (./compile.sh GCC debug) && (./compile.sh TCC debug)" <CR>
map <C-9> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh CLANG release) && (./compile.sh GCC release) && (./compile.sh TCC release)" <CR>


map <C-W> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh GLSLC debug)" <CR>
map <C-E> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh GLSLC release)" <CR>

map <C-A> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh TCC debug)" <CR>
map <C-F> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh GCC release)" <CR>
map <C-R> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh CLANG release)" <CR>

map <C-S> :execute "!clear && cd " . shellescape(vimrc_path) . " &&  ./run.sh" <CR>
map <C-D> :execute "!clear && cd " . shellescape(vimrc_path) . " &&  ./run.sh debug" <CR>
map <C-Q> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./run.sh detached)" <CR> <CR>


map <C-\> :tab split<CR>:exec("tag ".expand("<cword>"))<CR>
map <A-]> :vsp <CR>:exec("tag ".expand("<cword>"))<CR>


nnoremap <C-H> :tabprevious <CR> :redraw! <CR>
nnoremap <C-L> :tabnext     <CR> :redraw! <CR>

nnoremap <C-U> <C-W>h
nnoremap <C-I> <C-W>j
nnoremap <C-O> <C-W>k
nnoremap <C-P> <C-W>l
