# NZCP-Qt

A desktop version of [NZ Verifier App](https://en.wikipedia.org/wiki/NZ_Pass_Verifier) implementing the [NZ COVID Pass](https://github.com/minhealthnz/nzcovidpass-spec)  spec. Uses Qt and [NZCP.c](https://github.com/noway/nzcp-c) library.

Features
- URI verification via text
- QR Code verification via file

Contributions welcome! 🥳



## Screenshot
<img width="639" alt="Screen Shot 2022-01-14 at 1 45 36 AM" src="https://user-images.githubusercontent.com/2031472/149332717-cd9b94c3-b0a7-48f6-b065-0070fb633359.png">

<img width="639" alt="Screen Shot 2022-01-14 at 1 44 02 AM" src="https://user-images.githubusercontent.com/2031472/149332622-e6690407-8e7b-47f6-b88b-15d79d0f36c0.png">

## Requirements
- `qt@6`
- `zbar`
- `imagemagick@7`

## Build
- `qmake`
- `./build_nzcp`
- `make`

## Run
- `open nzcp-qt.app`

## Roadmap
- Publish a binary for Mac OS
- Better error handling
- Address/Memory Leak sanitization
