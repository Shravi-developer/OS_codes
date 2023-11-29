read -p "Enter the name of the file: " file_name


if [ -e "$file_name" ]; then
    
    file_type=$(file -b "$file_name")
    
   
    permissions=$(stat -c %A "$file_name")
    
    echo "File type: $file_type"
    echo "Permissions: $permissions"
else
    echo "File not found at path: $file_name"
fi
