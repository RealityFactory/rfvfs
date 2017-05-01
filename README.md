# rfvfs
Reality Factory VFS Explorer
----------------------------

The VFS Explorer allows you to combine most of your game resources (actors, bitmaps,
sounds and levels) into one large file, which can be accessed by Reality Factory. This
"Pack" or "VFS" file, as they are known, can also be encrypted to prevent others from
extracting and using your resources.

Using VFS Explorer
------------------

After running the program you will see a tree view of an empty Reality Factory resource
file directory and a column of buttons. These buttons are as follows :

New 	- emptys the tree view and sets up the default directory structure. All previous
	files will be lost.

Open	- opens a VFS file and displays it in the tree view. All previous files will be
	lost. If the VFS file is encrypted you will be asked to enter the encryption
	key before the file is opened.

Add	- adds files to the currently selected folder. Use Shift or Cntl to select
	multiple files to add.

Rename	- renames the selected file or folder.

Delete	- deletes the selected file or folder. You will be asked to confirm the deletion
	before it takes place. If a folder is deleted all the files in that folder are
	also deleted.

Extract	- extracts a file from the VFS file and saves to a user selected location.

MkDir	- creates a new subfolder of the currently selected folder. If a file is currently
	selected the folder that contains it will be used as the parent folder.

Save	- saves the tree view to a VFS file. If the "Use Encryption on Saving" box is
	checked then you will be prompted to enter the encryption key before the file
	is created.

Double clicking on a file in the tree view will open that file using the program that
Windows has associated with it.

Encryption
----------

VFS Explorer uses an encryption method of the "cheap lock" class. This will keep out the
honest folk but could be broken by a hacker. The encryption key used is 4 characters long,
although it can be shorter (giving less encryption). If you give the wrong key when opening
an encrypted file it will still load but the file contents will be garbage. No indication
is given that the wrong key was used, as VFS Explorer cannot tell if this happened. So
don't forget your encryption key. The current version of Reality Factory (0.5.4) does not
support encryption, although it will be in later versions.

General Information
-------------------

Not all resources can be placed in a VFS file. Those that can are :

	1. all actors
	2. all bitmaps
	3. most Wav files
	4. all level BSP files

What can't be placed in a VFS file are :

	1. Wav files used as streaming audio
	2. Midi files
	3. Avi files

These files are accessed directly by Windows, which cannot read them from a VFS file.

The current version of Reality Factory (0.5.4) attempts to load the resources from the
VFS file first, then checks the disk directory second. This will be swapped in later
versions so you can replace a resource simply by placing the new version in the correct
directory, where it will be loaded first.

The VFS file must reside in the same directory as realityfactory.exe in order for the 
file to be opened properly.

Minimum VFS Contents
--------------------

The following files are needed by Reality Factory as minimum resources in a VFS file. To
this list can be added all resources needed by your level(s). Note that the demo level
second.bsp uses the Wav file laughter3.wav and this is included in the Media\Audio
folder. It is not needed in the VFS file for minimum content.

Directory			File
---------			----
Media\Actors			bolt.act
				ernie.act
				grenade.act
				proj.act
				rocket.act
				vbat.act
				vchain.act
				vgrenade.act
				vmgun.act
				vrocket.act
				vsword.act
				wbat.act
				wchain.act
				wgrenade.act
				wmgun.act
				wrocket.act
				wsword.act

Media\Audio			bathit.wav
				bounce.wav
				bulletfire.wav
				grenade.wav
				grenexp.wav
				loopbzzt.wav
				mimpact.wav
				mlaunch.wav
				onebzzt.wav
				rockexp.wav
				rockfire.wav
				rockfly.was
				startup.wav
				swordhit.wav
				swordmiss.wav

Media\Audio\Menu		pop1.wav
				pop2.wav

Media\Bitmaps			a_bubl.bmp
				a_flame.bmp
				a_lvsmoke.bmp
				a_rain.bmp
				attitude_g.bmp
				attitude_i.bmp
				bolt.bmp
				bubl.bmp
				corona.bmp
				corona_a.bmp
				flame03.bmp
				g_bubble.bmp
				happiness_g.bmp
				happiness_i.bmp
				health_g.bmp
				health_i.bmp
				hud1.bmp
				lvsmoke.bmp
				mana_g.bmp
				mana_i.bmp
				rain.bmp
				rflogo.bmp

Media\Bitmaps\Explode		1exp01.bmp
				1exp02.bmp
				1exp03.bmp
				1exp04.bmp
				1exp05.bmp
				1exp06.bmp
				a_1exp01.bmp
				a_1exp02.bmp
				a_1exp03.bmp
				a_1exp04.bmp
				a_1exp05.bmp
				a_1exp06.bmp
				a_expl1.bmp
				a_expl2.bmp
				a_expl3.bmp
				a_expl4.bmp
				a_expl5.bmp
				a_expl6.bmp
				a_expl7.bmp
				a_sexp1.bmp
				a_sexp2.bmp
				a_sexp3.bmp
				a_sexp4.bmp
				a_sexp5.bmp
				a_sexp6.bmp
				a_sexp7.bmp
				expl1.bmp
				expl2.bmp
				expl3.bmp
				expl4.bmp
				expl5.bmp
				expl6.bmp
				expl7.bmp
				sexp1.bmp
				sexp2.bmp
				sexp3.bmp
				sexp4.bmp
				sexp5.bmp
				sexp6.bmp
				sexp7.bmp

Media\Explode\Fx		a_smk01.bmp
				a_smk02.bmp
				a_smk03.bmp
				a_smk04.bmp
				a_smk05.bmp
				a_smk06.bmp
				a_smk07.bmp
				a_smk08.bmp
				a_smk09.bmp
				a_smk1.bmp
				a_smk2.bmp
				a_smk3.bmp
				a_smk4.bmp
				a_smk21.bmp
				a_smk22.bmp
				a_smk23.bmp
				a_smk24.bmp
				a_smk25.bmp
				parti1.bmp
				parti2.bmp
				parti3.bmp
				parti4.bmp
				parti5.bmp
				parti6.bmp
				parti7.bmp
				parti8.bmp
				smk1.bmp
				smk2.bmp
				smk3.bmp
				smk4.bmp
				smk21.bmp
				smk22.bmp
				smk23.bmp
				smk24.bmp
				smk25.bmp
				smoke_01.bmp
				smoke_02.bmp
				smoke_03.bmp
				smoke_04.bmp
				smoke_05.bmp
				smoke_06.bmp
				smoke_07.bmp
				smoke_08.bmp
				smoke_09.bmp
				smoke_10.bmp

Media\Explode\Menu		a_cour8b.bmp
				a_cour11b.bmp
				a_cour12b.bmp
				a_cour14b.bmp
				a_cour16b.bmp
				a_cour20b.bmp
				a_cour25b.bmp
				a_credits.bmp
				a_crosshair.bmp
				a_cursor.bmp
				a_images.bmp
				a_images1.bmp
				a_remap.bmp
				a_titles.bmp
				background.bmp
				cour8b.bmp
				cour11b.bmp
				cour12b.bmp
				cour14b.bmp
				cour16b.bmp
				cour20b.bmp
				cour25b.bmp
				credits.bmp
				crosshair.bmp
				cursor.bmp
				images.bmp
				images1.bmp
				loading.bmp
				remap.bmp
				titles.bmp

Files Required for a Demo
-------------------------

To make a complete demo package of Reality Factory you must have these files. This assumes
you have placed all the .act, .bmp, .wav and .bsp files required by your level(s) into the
VFS file.

Directory			File
---------			----

<root>				d3ddrv.dll
				glidedrv.dll
				hud.ini (if required)
				menu.ini (or replacement ini file)
				player.ini (if required)
				pack.vfs (or replacement vfs file)
				realityfactory.exe
				realityfactory.ini
				softdrv.dll
				softdrv2.dll

<root>\Media\Audio		Any .wav files used for streaming audio

<root>\Media\Midi		Any .mid files used

<root>\Media\Video		Any .avi files used

