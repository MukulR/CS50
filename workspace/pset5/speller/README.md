# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

A lung disease caused by inhaling small dust and ash particles

## According to its man page, what does `getrusage` do?

returns resource usage

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Because they are pointers. Calculate takes a pointer value to operate on.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

It starts by uploading the characters individually into the char * array `word` then, it is checked in comparison to the DICTIONARY constant which is dictionaries/large, to see if that word exists.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf will scan with the %s format type until it detects whitespace. fgetc, however will scan each character at a time.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

So they don't get overwritten or changed. Constant variables cannot be changed.
