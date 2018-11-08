zathura - a document viewer
===========================

zathura is a highly customizable and functional document viewer based on the
girara user interface library and several document libraries.

Use
---
Compile and install zathura.
Place the python script `neovim-synctex` in a directory listed in $PATH.
Copy `tex.vim` or its content into `~/.config/nvim/ftplugin/tex.vim`.
Run zathura from within vim as `zathura -n SERVERNAME`, e.g. `exec 'silent !zathura -n ' . v:servername . ' somefile.pdf&'`. 

Requirements
------------

meson (>= 0.45)
gtk3 (>= 3.22)
glib (>= 2.50)
girara (>= 0.2.8)
sqlite3 (optional, >= 3.5.9)
check (optional, for tests)
intltool
libmagic from file(1) (optional, for mime-type detection)
libsynctex from TeXLive (optional, for SyncTeX support)
libseccomp (optional, for sandbox support)
Sphinx (optional, for manpages and HTML documentation)
doxygen (optional, for HTML documentation)
breathe (optional, for HTML documentation)
sphinx_rtd_theme (optional, for HTML documentation)

Note that Sphinx is needed to build the manpages.  If it is not installed, the
man pages won't be built. For the HTML documentation, doxygen, breathe and
sphinx_rtd_theme are needed in addition to Sphinx.

If you don't want to build with support for sqlite databases, you can configure
the build system with -Denable-sqlite=false and sqlite support won't be available.

The use of magic to detect mime types is optional and can be disabled by
configuring the build system with -Denable-magic=false.

The use of seccomp to create a sandboxed environment is optional and can be
disabled by configure the build system with -Denable-seccomp=false. The sandbox
will by default be set to "normal" mode, which should not interfere with the
normal operation of zathura. For strict sandbox mode set "sandbox strict" in
zathurarc. Strict sandbox mode will reduce the available functionality of
zathura and provide a read only document viewer.

Installation
------------

To build and install zathura using meson's ninja backend:

  meson build
  cd build
  ninja
  ninja install

Note that the default backend for meson might vary based on the platform. Please
refer to the meson documentation for platform specific dependencies.

Bugs
----

Please report bugs at http://bugs.pwmt.org or contact us on our mailing list at
zathura@lists.pwmt.org.
