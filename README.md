# OasisPro

## Important Notice (Part 1)

Please make sure to `comment your code` so that we can understand it as well as be able to debug it properly. This will also help us in explaining our code to our TA.

## Important Notice (Part 2)

To get the most updated version of the project, please type in gnome-terminal in the folder that you created as the repo for the project the following command: `git pull` as seen in the picture below. 

![](image/Image23.PNG)

## Timeframe

Some details on the important dates for this project. 

| Date(s)              | Importance            |
| -------------------- | --------------------- |
| December 12, 2022     | Finished all project  |
| December 14 to 15, 2022 | Meet with TA |

## Merge Errors

If you get errors with a merge, please follow the intructions in this [link](https://stackoverflow.com/questions/161813/how-do-i-resolve-merge-conflicts-in-a-git-repository) and use BA (Base) for when merging changes with the `mergetool`. 

## Important files

Please download, review, and read the following necessary files (the specification document will be added after consultation with the client) provided to us by our customer (client): 

[Download OASIS_Pro_Manual_v1r8.pdf](client/OASIS_Pro_Manual_v1r8.pdf)

## Client Demo Video

Click on the image below to watch the Oasis Pro demo video (this project will be partly based on this). 
<br>
<br>
[![Watch Oasis Pro Demo video](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSdUHycsxGxDWaGKb1WMPsf325BxuOMV0mn3z6H18SXzOULhURqQdiInSm2hqLYJ_q7tGs&usqp=CAU)](https://www.youtube.com/watch?v=PDgN03Fx6fg&t=2s)

## Team Number

```diff
Our team number is 37. 
```

## Milestones & Package Releases

Each milestone in this project will bring a package release showcasing what we have completed so far in this project. 

This project has 5 milestones (necessary), which are: 

- [x] Power which has `Turn On/Turn Off` and `Ending A Session` features as described on page 4 of the manual.
- [x] Battery level as described in section on page 5 of the manual. 
- [x] Selecting a session as per `Selecting A Session` on page 5 of the manual.
- [x] Connection test as per `Connection Test` on page 6 of the manual.
- [x] Intensity as per `Adjusting Intensity` on page 7 of the manual.

This project also has 2 additional milestones, which are: 

- [x] `Record feature` where users can choose to record a therapy and add to treatment history.
- [x] `Replay feature` where users can replay selected treatments from history of treatments.

## Relevant Documents

[Link to Use case document](https://docs.google.com/document/d/1MYg5dHoU1SRV3qOMvXtguB_YqrAV9xEW/edit)<br>
[Link to Traceability Matrix](https://docs.google.com/document/d/1dHgvpd0EOjXzUPfw5XxjvbdnfVWdI6Mz/edit)

## Tasks Assignment

| Team Members         | Tasks                 |
| -------------------- | --------------------- |
| Andre Nonaka Cordova | Readme.md<br>GUI Creation<br>Use Case Model<br>Traceability Matrix<br>Sequence Diagram <br> Activity Diagram<br> State Diagram <br> Connection Test Feature <br> Intensity Feature |
| Alex Nedev | Session Selection Feature<br>Replay Feature |
| Khaled Farag | UML Model<br>Power Feature<br>Battery Level |
| Mingrui Liang | Replay Feature<br>Record Therapy Feature |

## Status of OasisPro

Completed  &#9989;. 

## Progress Report Table

&#128994; = Completed<br>
&#128993; = In Progress<br>
&#128308; = Not Started

```
Notice 1: The Progress Report Table will need to be updated throughout the project. 
```

| Task             | Status          | Lead                  | Collaborators | Expected end date | Actual end date | Time spent | Notes |
| ---------------- | :-------------: | --------------------- | ------------- | ----------------- | --------------- | ---------- | ----- |
| Readme.md (will be continuously updated)       | 	 &#128994;     | Andre Nonaka Cordova  | Khaled Farag | 2022-11-25        | 2022-12-10      | 3 weeks      | N/A   |
| <br><br><br><br>Use Case Model and Traceability Matrix<br><br><br><br> |  &#128994;  | Andre Nonaka Cordova  | Alex Nedev | 2022-11-22 | 2022-12-10 | 3 weeks | Completed a Preliminary draft of the Use Cases.<br>However, we will most likely change certain cases as we move along in the project.<br> Alex N provided some feedback on Use Cases.<br>Will work back and forth with lead until we believe we’re done. |
|    UML Model     |   &#128994;     | Khaled Farag  | Andre Nonaka Cordova  | 2022-11-14 | 2022-12-08 | 4 weeks | The original UML model was made by Andre in mid November. As changes to the project made the original UML obsolete, it was overhauled by Khaled. |
| GUI Creation     |   &#128994;     | Andre Nonaka Cordova  | N/A  | 2022-11-14 | 2022-11-25      | 2 weeks | N/A |
| Power Feature    |   &#128994;     | Khaled Farag          | N/A | 2022-11-30 | 2022-11-30 | 2 weeks | Basic features were completed in <1 weeks; needed to wait for other features to be sufficiently completed to finish this one. |
| Battery Level    |   &#128994;     | Khaled Farag          | N/A  | 2022-11-30 | 2022-12-05 | 3 weeks | Basic features were completed in <1 weeks; needed to wait for other features to be sufficiently completed to finish this one. |
| Session Selection Feature |   &#128994;  | Alex Nedev   | Andre Nonaka Cordova  | 2022-11-30 | 2022-11-24      | 1 week | N/A |
| Connection Test Feature |   &#128994;  | Andre Nonaka Cordova  | Mingrui Liang | 2022-12-10 | 2022-12-05      | 1.5 week | N/A |
| Intensity Feature  |   &#128994;   | Andre Nonaka Cordova  | Alex Nedev   | 2022-11-18 | 2022-11-18      | 1 week | N/A |
| Record Therapy Feature (should have support for at least 4 users) |   &#128994;  | Mingrui Liang  | Andre Nonaka Cordova  | 2022-11-30 | 2022-12-10      | 1 week | N/A |
| Replay Therapy Feature (should have support for at least 4 users) |   &#128994;  | Alex Nedev | Mingrui Liang | 2022-11-30               | 2022-12-10      | 1 week | N/A   |

## How to work on this project in your personal computer

To begin, we have to make sure that you have installed git in your virtual machine. To check this, type in gnome-terminal `git --version` as seen in the picture below. Make sure that you receive a version for your git and not an error. 

![](image/Image1.PNG)

After this, we will need to create a local repository that store a clone of the project somewhere in your computer. In my workspace, I created mine in my desktop as seen in the image below (circled in blue). 

![](image/Image2.PNG)

After this go to the directory of that folder as seen in the image below. 

![](image/Image3.PNG)

After this clone this repository by using the `git clone` command followed by this link: https://github.com/Andre-Nonaka/OasisPro.git as seen in the image below. 

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

Once you have generated your personal access token, copy and paste it into the gnome-terminal for your password. After processing your login information, the clone of the repository should be added to your repository folder in your personal computer (or virtual machine). You can check if you have OasisPro folder in your repo by typing `ls` in gnome-terminal as seen in the image below. 

![](image/Image12.PNG)

To check if your initial commit was made (this commit would be the cloning of the repository), type `git log` in gnome-terminal as seen in the image below (mine will have many logs as I have already committed multiple items to the repository, but yours should have only one named `initial commit` if it is your first time working on this repository). 

![](image/Image13.PNG)

Now that we have finished and confirmed that we cloned our repository, we will need to ensure that our Qt Creator application is configured to push, pull, and commit files to the local and remote repository. First we will open the project from the repository into the Qt Creator application as seen in the image below.

![](image/Image14.PNG)

After opening the project in Qt Creator, we will need to check if the project has the path for the git binary file configure in it. To check this, go to the `Tools tab` and select the `Options tab`. From there go to the `Version Control section` and check the `Configuration` path. If it is empty please enter the path to where the git binary file is stored at within your personal computer or virtual machine as seen in the image below. 

![](image/Image15.PNG)

After this, you will be able to push, commit, and pull the files to the local and remote repository. Once you have finish editing the project, it will be time to commit your changes to the repository. To do this, we will need to first add the files to our list of files to commit using `git add -A` or `git add .` as seen in the image below.

![](image/Image22.PNG)

After this, type in gnome-terminal `git commit -m "Put whatever you want here"` as seen in the image below. 

![](image/Image16.PNG)

After doing this, we will pull from the repository any new updated or added files using `git pull` as seen in the images below (remember that your password is the personal access token you created in your Github account and not your actual password).

![](image/Image17.PNG)

![](image/Image18.PNG)

After pulling the files, you will be able to push your newly created commit to the repository using `git push origin main` or `git push -u origin main` as seen in the image below (remember that your password is the personal access token you created in your Github account and not your actual password).

![](image/Image19.PNG)

Using these instructions, you will now be able to fully update and push your changes to the project without any issues. 
