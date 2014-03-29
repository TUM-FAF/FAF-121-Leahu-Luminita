# IDE Laboratory Work #1

### Title: Command Line Interface. CLI Editor. Setting Server environment. Version Control Systems.

#### In this laboratory work I executed the following mandatory tasks:

   - **Connect to a remote server via SSH**

	In order to do this I used `putty` program. 
   - **Initialize a repository on server**
   
	`git init`
   - **Create a file in repository folder, write in your name, save and commit it**
  
   	 ```
	 mkdir Luminita 	# create a folder
	 vim text.txt   	# editor to create a text file
	 i              	# enter an insert
	 Luminita Leahu		# your text 
	 :wp				# write into file and exit
	 git add text.txt   # add the file to folder
	 git commit -m "added file with my name"

	 ```
#### Tasks with points:

   - **Create 2 more branches with at least one unique committed file per branch**
   In order to do this I executed following commands:
	```
	git init
	touch file.txt	             # creates a file		
	git add file.txt             # adds file to branch _master_
	git commit -m  "commit to master branch"
	git branch testbranch        # creates branch _testbranch_
	git branch -a                # displays all branches and shows i which one are you now
	git chekout testbranch       # switched to branch _testbranch_
	touch file1.txt		     	 # creats a txt file
	git add file1.txt            # adds this file on _testbranch_
	git commit -m 'commit on testbranch'
	```
	Now when I'm using `git checkout master` there will be _file.txt_ in my folder, if I write `git checkout testbranch` will be both files.

   - **Set a branch to track a remote origin on github**

    ```
    git remote add origin < URL address > # add a remote origin
    git push -u origin master             # push
    ```

   - **Reset a branch to previous commit, reset a branch to some specific commit**

     - Reset a branch to previous commit:
       `git reset --hard HEAD`  # where _HEAD_ is the last commit ID in  current branch
     - Reset a branch to some specific commit :
       ```
       git log             # displays all commits, find here the commit to reset
       git reset --hard ID # put instead of _ID_ finded commit ID

       ```
   - **Restore a reset branch back to its previous state**

      `git reset --hard ID`

   - **Master any CLI editor (VIM). Learn 10 commands' sets**
       
       1. `VU` - uppercase line
       2. `Vu` - lowercase line
       3. `ggguG` - lowercase all text
       4. `?word` - search _word_ from bottom to top
       5. `/word` - search _word_ from top to bottom
       6. `:%s/$/word/g` - add _word_ at the end of each line
       7. `:%s/word1/word2/g` - replace _word1_ by _word2_ in all the file
       8. `:g/word/d`  - delete all lines containing _word_
       9. `:vsplit file` - split window vertically
       10. `:hide` - close current window
       11. `:q`    - exit Vim
       12. `:w`    - save file
       13. `:args` - list files
       14. `:tabnew` - creates a new tab 

   - **Create a VCS merge conflict and solve it**

      Conflict appears when a specific file is edited on two different branches. 
      [branches](https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%231/branches.png)

      - Create a VCS merge conflict:
        ```
        touch file.txt
        vim file.txt    # write some text 
        git add file.txt
        git commit -m "first commit"
        git checkout -b test  # switvh to a new branch _test_
        vim file.txt     # make changes in file 
        git add file.txt
        git commit -m "added file to test branch"
        cat file.txt # some text in conflict branch
        git checkout master # switch to master branch
        cat file.txt # some text in master branch
        git checkout master 
        vim file     # edit the file
        git commit -a -m "divergent commit"

        git merge conflict # CONFLICT <content>: Merge conflict in file.txt
        
      In order to solve the conflict:
        ```
        vim file     
        git commit -a -m "solve merge conflict"
        
        ```


