git checkout master
read -p "[+] Do you want to pull? (y/n): " input

if [[ "$input" == "y" ]]; then
    # git fetch origin
    git pull origin master
fi