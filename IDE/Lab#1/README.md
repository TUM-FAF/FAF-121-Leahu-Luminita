# IDE Laboratory Work #1

### Title: Command Line Interface. CLI Editor. Setting Server environment. Version Control Systems.

#### In this laboratory work I executed the following mandatory tasks:

   - **Connect to a remote server via SSH**
   - 
	In order to do this I used `putty` program. 
   - **Initialize a repository on server**
   
	`git init`
   - **Create a file in repository folder, write in your name, save and commit it**
  
   	 ```
	 mkdir Luminita 	// create a folder
	 vim text.txt   	// editor to create a text file
	 i              	// enter an insert
	 Luminita Leahu		// your text 
	 :wp				// write into file and exit
	 git add text.txt   // add the file to folder
	 git commit -m "added file with my name"

	 ```
#### Tasks with points:

   - **Create 2 more branches with at least one unique committed file per branch**
   In order to do this I executed following commands:
	``
	git init
	touch file.txt	             // creates a file		
	git add file.txt             // adds file to branch _master_
	git commit -m  "commit to master branch"
	git branch testbranch        // creates branch _testbranch_
	git branch -a                // displays all branches and shows i which one are you now
	git chekout testbranch       // switched to branch _testbranch_
	touch file1.txt		     // creats a txt file
	git add file1.txt            // adds this file on _testbranch_
	git commit -m 'commit on testbranch'
	``
	Now when I'm use `git checkout master` there will be _file.txt_ in my folder, if I write `git checkout testbranch` will be both files.
