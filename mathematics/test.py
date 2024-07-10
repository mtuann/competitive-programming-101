import re

def replace_text_in_file(file_path):
    with open(file_path, 'r') as file:
        content = file.read()
    
    # Use regular expression to find and replace the pattern
    modified_content = re.sub(r'\$ (\w+) \$', r'$\1$', content)
    
    with open(file_path, 'w') as file:
        file.write(modified_content)

# Example usage
file_path = '/Users/tuan/Desktop/house/cp-training/mathematics/cses1712-phi-euler.md'  # Replace with the path to your text file
replace_text_in_file(file_path)
