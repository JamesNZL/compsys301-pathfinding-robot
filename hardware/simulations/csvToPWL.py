import os
import csv

def copy_files_except_first_two_lines(source_dir, dest_dir):
    if not os.path.exists(dest_dir):
        os.makedirs(dest_dir)
    
    for filename in os.listdir(source_dir):
        if filename.endswith(".csv") or filename.endswith(".CSV"):  # only process CSV files
            source_file = os.path.join(source_dir, filename)
            if filename.endswith(".csv"):
                dest_file = os.path.join(dest_dir, filename.replace('.csv', '.txt'))
            else: 
                dest_file = os.path.join(dest_dir, filename.replace('.CSV', '.txt'))

            with open(source_file, 'r') as in_f, open(dest_file, 'w') as out_f:
                csv_reader = csv.reader(in_f)
                
                # Skip first two lines
                next(csv_reader)
                next(csv_reader)

                # Copy the rest
                for row in csv_reader:
                    # Write row as tab-separated line
                    out_f.write('\t'.join(row) + '\n')

# use the function
copy_files_except_first_two_lines('C:\\Users\\AKLbc\\Desktop\\301\\hardware\\photodiode', 'C:\\Users\\AKLbc\\Desktop\\301\\hardware\\simulations\\Photodiode PWL Sources')
