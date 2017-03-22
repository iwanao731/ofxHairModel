# ofxHairModel

This addon is possible to import hair model and view it.

<img src="top.png" alt="hair result" width="600px">

## Environment
  + Windows 10
  + openFrameworks v0.9.3
  + Visual Studio 2015

## Dependencies
  + <a href="https://github.com/weshoke/ofxHEMesh">ofxHEMesh</a>
  + <a href="https://github.com/elliotwoods/ofxRay">ofxRay</a>
  + <a href="http://eigen.tuxfamily.org/index.php?title=Main_Page">Eigen Library</a> for using ofxHEMesh

## How To Use?
  1. Please put this folder to addon folder.
  2. Please download hair and face database from Hair Database below.
  3. Please put them in ofxHairModel\example-simpleViewer\bin\data".
  4. Please run projectGenerator and select this folder. Then you should select addons written above.
  5. Please change the filename in src/ofApp.cpp.

          void ofApp::setup(){
          	string hairname = "strands00001.data"; // USC-HairSalon Model
          	string filename = "head_model.obj";

          	hairModel.loadHairModelUSC(hairname);  // for USC-HairSalon
          	//hairModel.loadHairModel(hairname);   // for ReducedHairModel

          	hairModel.exportHairModelAsText("exported_" + hairname);
          	mesh.loadOBJModel(filename);

            ...
          }

  6. Run!

## Hair Database
+ A Reduced Model for Interactive Hairs [<a href="http://gaps-zju.org/reducedhair/">link</a>]
+ USC-HairSalon: A 3D Hairstyle Database for Hair Modeling [<a href="http://www-scf.usc.edu/~liwenhu/SHM/database.html">link</a>]
 (TBD...)  
