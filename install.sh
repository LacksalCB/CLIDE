#!/bin/bash

# Detect OS and determine install path 

# Retrieved from: https://gist.github.com/prabirshrestha/3080525

CLIDE="clide"
UNAME=$( command -v uname)
case $( "${UNAME}" | tr '[:upper:]' '[:lower:]') in
  linux*)
    echo 'OS: linux';
    INSTALL_PATH="$HOME/.local/share/$CLIDE"; 
    ;;
  darwin*)
    echo 'OS: MacOS';
    INSTALL_PATH="$HOME/Library/Application Support/$CLIDE"; 
    ;;
  *)
    echo 'OS: Unknown';
    exit
    ;;
esac

echo "Copy templates to system?" 

select strictreply in "Yes" "No"; do
    relaxedreply=${strictreply:-$REPLY}
    case $relaxedreply in
        Yes | yes | y ) echo "Installing templates..."; cp -r templates/* "$INSTALL_PATH"; break;;
        No  | no  | n ) exit;;
    esac
done

echo "$INSTALL_PATH"

if [ ! -d "$INSTALL_PATH" ]; then
    echo 'Creating program data...'
    mkdir -p "$INSTALL_PATH"
fi

echo "Finished install"

