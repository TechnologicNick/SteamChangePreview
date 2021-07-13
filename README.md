# SteamChangePreview
A commandline tool to change the preview image of Steam Workshop items.

## Installation
1. Download the latest `SteamChangePreview-release.zip` from the [Releases](https://github.com/TechnologicNick/SteamChangePreview/releases) page.
2. Extract the .zip archive.

## Usage
> **NOTE:** Make sure Steam is running and you're logged in with an account that's allowed to change the preview image.

1. Drag and drop the image you want to use onto `SteamChangePreview.exe`.
2. Enter the publishedfileid of your workshop item.
<br> This can be found at the end of the URL of your workshop item. For a given workshop item with URL `https://steamcommunity.com/sharedfiles/filedetails/?id=2542032886` the publishedfileid is `2542032886`.
3. Enter the appid of the game of your workshop item.
<br> You can find the appid by looking for the game on [SteamDB](https://steamdb.info/).
<br> Leave blank to automatically detect the appid of **public or unlisted** workshop items. If this fails the previously used appid is used as a fallback.

This should have changed the preview image of your workshop item. If an error occured, the code, name and description are displayed to give an idea on how to solve it.

## CLI
Usage: `SteamChangePreview.exe IMAGE_PATH PUBLISHEDFILEID [APPID] [OPTIONS]`

Options:
* `-h`, `--help` - Show usage
* `--hidemessagebox` - Prevent the messagebox from being shown

Fields that are not filled in will be taken from `stdin`.

## Known problems
* Unicode characters in the image path do not work. This is a limitation of the SteamAPI and I am unable to find a workaround for it.
