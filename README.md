# jakx-c-kernel-decompiled

## `kernel/jakx`

This project's primary purpose is to provide for the `game/jakx` and `common/jakx` C++ code for the OpenGoal Project, necessary to run Jak X. As the game also useses networking, we try to reverse the rest of the (SCE-RT) functions' labels (Medius, etc.) so that the game can hopefully be connected to unofficial fan-hosted servers. Even _if_ we'd step away from Medius code in the client-side of the game, it's still useful to see what the names are of network related C function calls in GOAL code during GOAL decompilation. This way, people decompiling that GOAL code can better guess/understand what that GOAL code calling those functions is doing.

## GOAL decompilation

As said, this project will focus on the C++ part of the code base, with the intention of merging/bringing it later back into the OpenGOAL project. Regarding the part of the codebase that consist of GOAL code, initial work has already been done to start decompilation in [this pull request](https://github.com/open-goal/jak-project/pull/3633).

## ELF overview

There are 4509 occurrences of the pattern `"function"` in that dump, which should be the exact number of functions reversed. There might be a handful of functions that have not been disassembled (discovered) yet, but that number should be low. There are 1478 occurrences of the regex pattern `"FUN_........"`, hence a third of all functions have no information at all on known functions (yet). There are 1817 occurrences of the regex pattern `".*FUN_.........*"`, so additional information is available on about 300 of them, and this should be the number of functions that could not be matched. They are however not necessary to port the game, but they _might_ make it a little bit easier.

## Symbol matching

In order to make sense of the ELF, I've been primarily adding symbol names, which is what I refer to "symbol matching". Unlike efficient approaches, I've been working from the ground up: I've invested time in adding as much symbols as possible before trying to export decompiled code.

### Matching sources

I matched against several bsim servers that held the definitions of the following games. I looked at games around the same date that would have a shared codebase (i.e., Jak and Daxter, obvisouly, Medius, or simply around 2005, the release of Jak X). Retro Reversing has listed a few [PS2 games with unstripped symbols](https://www.retroreversing.com/ps2-unstripped/) and [PS2 demos with symbols](https://www.retroreversing.com/ps2-demos/).

- [My Street](https://en.wikipedia.org/wiki/My_Street) (March 9, 2003)
- demo of [Ratchet and Clank: Deadlocked](https://en.wikipedia.org/wiki/Ratchet:_Deadlocked) (September 2005)
- demo of [Jak 3](https://en.wikipedia.org/wiki/Jak_3) (August 24, 2004)
- demo of [God of War II](https://en.wikipedia.org/wiki/God_of_War_II) (May 5, 2006, or 27 February, 2007)

Next to that, I also got symbols from the [PS2SDK project](https://github.com/ps2dev/ps2sdk), where I could compare strings at best, or compare enums or other variables at worst. Sometimes I also copied over signatures from there.

### Naming convention

My naming scheme changed over time as I noticed I needed to be more precise on where my symbols came from and how well I could trust them. This means that I cannot describe something here that will definitely fit all situations. I usually copied over the names and added a suffix, i.e. `foo_G`.

- `_G`: Usually, I find these symbol names in other guess symbols, but I'm not entirely sure as they are not matching perfectly. Careful though, the names may also be completely made up, so check the above referene symbols. With global variables, this is usually made clear by using `ALL_CAPS_STYLE_G`, but not consistent.
- `_S`: These symbol names are based on a string. This means I'm already confident I'm correct (I used to use `_G` or `_Q` for this as well). Later on, I typically remove these labels either way. Some names cannot be verified and in those cases, I would rarely removed the suffix. (Example: `FUN_00133cc8_addPurchase` calls `addPurchase_S` and also prints `"addPurchase error"` after checking its result.)
- `_Q`: These symbol names are either guessed by matching functions recursively in BSIM search windows, or based on strings. In general, I was moderatly confident they were right, but wanted to come across another occurrence I could verify to be absolutely sure. I later started to use `_S` for string sources that would give away a name.
- `_W`: I'm guessing a name wildly, based on some function body or data structure that is related somewhere. (I used to use `_G` for this as well.)
- `_T`: The source is one of the tables; depending on how certain I am, it will be combined with `W`, `G` or nothing.
- no prefix: This may mean I'm sure it's correct ***or*** that I named the symbol that way early on when I wasn't careful and it might even be made up, or simply a guess.

### Symbol Transfer

The address of the binary dump from PCSX2 and the decrypted ELF match exactly. As most of the initial work was still in the memory dump, which was the most relevant for the decompilation of the `game/jakx` and `common/jakx` C++ code, I created a few scripts to go through the code and usually interactively ask whether to override a symbol or not.

To execute them, I simply copied over the code into Ghidraton (but the Python Window should work to with some small changes, normally). Most scripts (are horribly coded but) work fine. It is recommended though to minimally understand what the scripts do, after all they're small anyway. If you're not familiar with the Ghidra API, some knowledge on them could always be handy --- you could ask Perplexity/ChatGPT, as they surprisingly know the API very well!

In one of the scripts, you might be getting this error when you try to apply a signature override in Ghidra. (I came across it when doing this manually.) This should occur whenever the function call has a BLUE label "ptr_addr1_addr2". If it's either WHITE or simply "LAB_addr", then it's fine and shouldn't happen.

```
Error overriding signature: ghidra.util.exception.InvalidInputException: DataTypeSymbol has a reference
---------------------------------------------------
Build Date: 2024-Jun-07 1416 EDT
Ghidra Version: 11.1
Java Home: C:\Program Files\Eclipse Adoptium\jdk-17.0.11.9-hotspot
JVM Version: Eclipse Adoptium 17.0.11
OS: Windows 10 10.0 amd64
Workstation: REUBUS
```

To resolve the above error from appearing (for that function call signature override), simply remove the ptr label, so that it will be a blue "LAB_addr" label, and try again. You might be able to execute the signature override, I wasn't as I think I ran against a [bug that might get fixed in the future](https://github.com/NationalSecurityAgency/ghidra/issues/7322). (The code is of course perfectly fine ;p)

### String Tables

*From what I understand from Perplexity*, string tables are used for symbol resolution and to serve as debugging information. The ones I found all 10 reside in `.text`, but sadly, somewhere around function `entry`, they stopped appearing. I have labeled the start of the string tables with `CPP_FILE`.

I've used a prompt to apply these names as Perplexity is very good at transforming these strings into *signatures*, but they require double checks. Additionally, the return types appear not to be reliable --- is it even part of those strings? Further down in [this conversation](https://www.perplexity.ai/search/in-my-elf-game-i-found-this-in-YKclb.1KRSiQTz7Sv34SHQ), you can find a few examples that are useful to learn how to interpret these strings. The prompt that gave okay results is the following:

```
I'm trying to figure out the signature of a symbol that I found in a C++ string table for symbol resolution and debugging. What would be the signature of the following mangled name: _videoCallbackEP7sceMpegP16sceMpegCbDataStrPv.
```

## Todolist

Large tasks:

- [ ] Although I don't expect to gain much from it, one can try to match the functions against those of Jak 1 or Jak 2.
- [x] `gcc2_compiled.` functions in other (demo) games have additional labels that give away their names, apparently. I noticed this too late, but it would be helpful to locate other nameless functions if we can match these gcc functions.
- [x] Apply mangled symbol names from tables (under `CPP_FILE`) if reliable.
- [ ] Find source of orphaned strings (`001eba50`, `001e78b0`, `001e78d0`, ``)

Less important details to check:

- [ ] Is `DAT_001f63e0` (or lower) an array of thread ids?
- [ ] What are these functions for?  
  ```
  DAT_001f5b78_func1 = 0;
  DAT_001f5b7c_func2 = 0;
  DAT_001f5b80_func3 = 0;
  ```
- [ ] Compare print functions with new sources. NOTE: the print functions are a mess, don't try to fix their names, as sources will contradict. (For example, `fiprintf` in all binaries call each `_vfiprintf_r`, but differently.)
- [ ] ... many more that I forgot to write down.
