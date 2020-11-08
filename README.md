# x

Personal little experiment to write a little unified package manager facade.

This is just a funny little project and not destined at larger usage.

## usage

An operation is done by using a token followed by the package name.

- Install a program: `+<program>`
- Remove a program: `-<program>`
- Update a program: `^<program>`

## examples

Let's say we want to install vim, remove neofetch and update gcc

```
$ x +vim -neofetch ^gcc
```

(you can chain as many operations as you want)

There's even a shortcut to update all installed packages:

```
$ x ^
```

# Supported package managers

- Brew (will be used in case OS == MacOS)
- APT (will be used in case OS == linux)
- Chocolatey (will be used in case OS == windows)

# Why?

... Because why not?

# I want to install it

You shouldn't, but here's how to do it:

```
$ cargo install --path .
```