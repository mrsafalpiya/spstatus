# spstatus - Safal Piya's Status (bar for dwm)

Very (very) simple status bar for dwm.

## What does it do?

For now, it simply shows time in the dwm's status bar by setting up the
X server's root window name.

## How do I get more out of it?

Just code it. Duh.

Any subsequent users are intended to code out their own personal needs. For me
personally, a time is sufficient.

## Installation

First run

```
$ make
```

This will build out the `spstatus` executable in the current folder.

Then run

```
# make install
```

To install it on your system.

## Run at startup

### For users using `startx` to start up X

Just add `spstatus &` in your `.xinitrc` file located in your home directory
before the line `exec dwm` (as it should always be at the last).

### For others

RTFM your display manager's arch wiki page.
