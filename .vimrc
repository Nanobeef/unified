set autoread

let working_path = getcwd()
let vimrc_path = expand('<sfile>:p:h')



map <C-0> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh TCC debug)" <CR>
map <C-9> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh GCC debug)" <CR>
map <C-8> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh CLANG debug)" <CR>
map <C-1> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh CLANG debug) && (./compile.sh GCC debug) && (./compile.sh TCC debug)" <CR>


map <C-A> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh GCC debug)" <CR>
map <C-F> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh GCC release)" <CR>
map <C-S> :execute "!clear && cd " . shellescape(vimrc_path) . " &&  ./run.sh" <CR>
map <C-D> :execute "!clear && cd " . shellescape(vimrc_path) . " &&  ./run.sh debug" <CR>
map <C-Q> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./run.sh detached)" <CR> <CR>

map <C-F8> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh clean) " <CR>
map <C-F9> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh clean) && (./compile.sh)" <CR>
map <C-F10> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh clean) && (./compile.sh release)" <CR>
map <C-F11> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh clean) && (./compile.sh release all)" <CR>
map <C-F12> :execute "!clear && cd " . shellescape(vimrc_path) . " &&  ./run.sh all" <CR> <CR>

map <C-\> :tab split<CR>:exec("tag ".expand("<cword>"))<CR>
map <A-]> :vsp <CR>:exec("tag ".expand("<cword>"))<CR>


nnoremap <C-H> :tabprevious <CR> :redraw! <CR>
nnoremap <C-L> :tabnext     <CR> :redraw! <CR>

nnoremap <C-U> <C-W>h
nnoremap <C-I> <C-W>j
nnoremap <C-O> <C-W>k
nnoremap <C-P> <C-W>l
