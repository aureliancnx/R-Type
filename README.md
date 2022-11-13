[![KapEngine](https://img.shields.io/badge/KapEngine-brightgreen.svg)](https://github.com/benji-35/KapEngine/)
[![KapMirror](https://img.shields.io/badge/KapMirror-brightgreen.svg)](https://github.com/Chaika9/KapMirror/)
[![SylphTransport](https://img.shields.io/badge/SylphTransport-brightgreen.svg)](https://github.com/Chaika9/SylphTransport/)
[![KapUI](https://img.shields.io/badge/KapUI-brightgreen.svg)](https://github.com/benji-35/KapUi)
[![Documentation](https://img.shields.io/badge/docs-brightgreen.svg)](https://chaika9.gitbook.io/rtype/)
[![Release](https://img.shields.io/github/release/aureliancnx/R-Type.svg)](https://github.com/aureliancnx/R-Type/releases/latest)
[![Build verification](https://github.com/aureliancnx/R-Type/actions/workflows/build.yml/badge.svg)](https://github.com/aureliancnx/R-Type/actions)
[![License: GPL-3.0](https://img.shields.io/badge/License-GPL--3.0-brightgreen.svg)](https://github.com/aureliancnx/R-Type/blob/main/LICENSE)

<img src="https://fs-prod-cdn.nintendo-europe.com/media/images/10_share_images/games_15/virtual_console_wii_u_7/H2x1_WiiUVC_RType.jpg" title="R-Type" alt="Image"/>

## R-Type

## How do I build and run this?
See the [R-Type build instructions](https://chaika9.gitbook.io/rtype/user-manuel/build-instructions). R-Type runs on Linux, MacOS (intel) and Windows.

## Install the game

The game installer is available for Windows, Mac OS and Linux on the [release page](https://github.com/aureliancnx/R-Type/releases) of the game.

You can also run the game from a build version directly without installer (portable version) by using the tarball files also available in the [game releases](https://github.com/aureliancnx/R-Type/releases).

You may find the [latest game release here](https://github.com/aureliancnx/R-Type/releases/latest).

## Host your own server
You're able to directly run the R-Type server without building the project. Just do it by downloading the latest [Docker](https://docs.docker.com/engine/install/) image available.

```
$ docker pull aureliancnx/rtype-server:latest
$ docker run -p 7777:7777 -it aureliancnx/rtype-server:latest
```

You can retrieve the Docker image here : [aureliancnx/rtype-server](https://hub.docker.com/repository/docker/aureliancnx/rtype-server)

The **latest** Docker image is automatically updated with Github Actions when a game release is created.

## Documentation
- [R-Type Documentation](https://chaika9.gitbook.io/rtype/)
- [KapEngine Documentation](https://kap35.gitbook.io/kap-engine-wiki/)
- [KapMirror Documentation](https://chaika9.gitbook.io/kapmirror/)

## How organize project
- Library : Folder that contains all the libraries used by the project.
- Assets : All additional things useful for the gameplay (Components, Textures, Font, ...).
- Package : All additional things useful for background logic (Raylib encapsulation, ...).

## Cheat warning

This repository is public for several technical reasons. Do not use this repository for a school project at EPITECH, to avoid being flagged for cheating (-42). We are not responsible for the use you make of our repository.

## Authors

<table>
    <tbody>
        <tr>
            <td align="center"><a href="https://github.com/Chaika9/"><img src="https://avatars.githubusercontent.com/u/30606616?v=4?s=100" width="100px;" alt="Chaika9"/><br /><sub><b>Chaika9</b></sub></a><br /></td>
            <td align="center"><a href="https://github.com/aureliancnx/"><img src="https://avatars.githubusercontent.com/u/72009413?v=4?s=100" width="100px;" alt="aureliancnx"/><br /><sub><b>aureliancnx</b></sub></a><br /></td>
            <td align="center"><a href="https://github.com/benji-35/"><img src="https://avatars.githubusercontent.com/u/72010213?v=4?s=100" width="100px;" alt="benji-35"/><br /><sub><b>benji-35</b></sub></a><br /></td>
            <td align="center"><a href="https://github.com/Ewen02/"><img src="https://avatars.githubusercontent.com/u/72020898?v=4?s=100" width="100px;" alt="Ewen02"/><br /><sub><b>Ewen02</b></sub></a><br /></td>
            <td align="center"><a href="https://github.com/DosserPaul/"><img src="https://avatars.githubusercontent.com/u/72012163?v=4?s=100" width="100px;" alt="DosserPaul"/><br /><sub><b>DosserPaul</b></sub></a><br /></td>
            <td align="center"><a href="https://github.com/meredith-lbj/"><img src="https://avatars.githubusercontent.com/u/72020241?v=4?s=100" width="100px;" alt="meredith-lbj"/><br /><sub><b>meredith-lbj</b></sub></a><br /></td>
        </tr>
    </tbody>
</table>
