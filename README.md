# OasisPro

## How to work on this project in your personal computer

To begin, we have to make sure that you have installed git in your virtual machine. To check this, go to gnome-terminal and type git --version as seen in the picture below. Make sure that you receive a version for your git and not an error. 

![](image/Image1.PNG)

After this, we will need to create a local repository that store a clone of the project somewhere in your computer. In my workspace, I created mine in my desktop as seen in the image below (circled in blue). 

![](image/Image2.PNG)

After this go to the directory of that folder as seen in the image below. 

![](image/Image3.PNG)

After this clone this repository by using the git clone command followed by this link: https://github.com/Andre-Nonaka/OasisPro.git as seen in the image below. 

![](image/Image4.PNG)

After running the above command, you will be asked to enter your username and password. For your username, it is the username of your github account, while the password is the personal access token you will need generate from Github by going to your settings and selecting developer settings followed by personal access tokens as seen in the images below (follow the steps outlined in the images below).

Step 1
![](image/Image5.PNG)

Step 2
![](image/Image6.PNG)

Step 3
![](image/Image7.PNG)

Step 4
![](image/Image8.PNG)

Step 5
![](image/Image9.PNG)

Step 6
![](image/Image10.PNG)

Step 7
![](image/Image11.PNG)

Once you have generated your personal access token, copy and paste it into the gnome-terminal for your password. After processing your login information, the clone of the repository should be added to your repository folder in your personal computer (or virtual machine). You can check if you have OasisPro folder in your repo by typing ls in gnome-terminal as seen in the image below. 

![](image/Image12.PNG)

To check if your initial commit was made (this commit would be the cloning of the repository), type git log in gnome-terminal as seen in the image below. 

![](image/Image13.PNG)

Now that we have finished and confirmed that we cloned our repository, we will need to ensure that our Qt Creator application is configured to push, pull, and commit files to the local and remote repository. First we will open the project from the repository into the Qt Creator application as seen in the image below.

![](image/Image14.PNG)

After opening the project in Qt Creator, we will need to check if the project has the path for the git binary file configure in it. To check this, go to the Tools tab and select the Options tab. From there go to the Version Control section and check the Configuration path. If it is empty please enter the path to where the git binary file is stored at within your personal computer or virtual machine as seen in the image below. 

![](image/Image15.PNG)
