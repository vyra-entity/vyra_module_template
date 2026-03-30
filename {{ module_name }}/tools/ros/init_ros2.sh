if [ -n "$BASH_VERSION" ]; then
    source /opt/ros/kilted/setup.bash
    source /workspace/install/setup.bash
elif [ -n "$ZSH_VERSION" ]; then
    source /opt/ros/kilted/setup.zsh
    source /workspace/install/setup.zsh
else
    echo "Unbekannte Shell: $SHELL"
fi