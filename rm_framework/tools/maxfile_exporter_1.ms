clearListener()


-- 0709622 Zsombor
-- exporter for the maxfile format 

--notes:
-- this version rescales the whole thing to be 1 unit height
-- only exports visible objects
-- attaches all the objects in the scene together --- it doesn't combine the materials though, so dont use multiple textures unless you want weird results
-- some other stuff i forgot about
-- dont need to rotate anything -- converts coordinates to opengl
-- i think vertices are in the default ccw order that opengl uses


---sometimes it cannot find texture verts
-- sometimes it can
-- ????


-- *** warning messy code ahead ***

--the function that does that trick
fn exportTheModel filename =
	(
		--open file
			out = createfile filename --fopen filename "wb" 
		
		
		--process the mesh into shape
		  --(most of the code is copied over from my own formats exporter, so its a mess)
		
		--first make a temporary mesh
		emesh = Editable_mesh() 
		
		--find and add the first visible mesh
			temp = 0
										for ob in geometry do
										(
											if ob.isHidden == false then 
												(
													temp = ob
													exit 									--exit loop - we found our man
													)--endif
													
											)--next ob

										--set empty editable emeshes mesh the first nonvisible meshes mesh -- (try saying this 10 times fast) (indeed)
											c = snapshotasmesh temp
												emesh.mesh = c.mesh
													delete c
		--add the rest of the visible meshes
			for obj in geometry do
					(
						if obj != emesh then 												--dont attach itself
							(
								if obj.isHidden != true then 								--dont attach hidden objects
									(
										if obj != temp then  								--temp was already attached
											(
												c = snapshotasmesh obj
												
													attach emesh c
												
														delete c
											)--endif
									)--endif
							)--endif
					)--next obj
				
					
					---***************** try to add some checkbox to toggle this feature ****************
		--move to center and stuff
					
					
		--move to center
			move emesh [0, 0, 0-emesh.center.z]
		
			mymesh = snapshotAsMesh emesh
			
		--1 unit height conversion
			u = 1 / (emesh.max.z - emesh.min.z) -- 1 / height of mesh
					
		---**********************************
		
		--might need to change this one as well -- since maxfile is drawn triangle by triangle anyway -- err so it works differently			
		
		--build arrays

				--export number of tex coordinates or vertex coordinates?
						-- if we got more tex coords, export based on that
						-- and then we base the indices on the face texes
						--luckily we got same number of texture faces as faces
				numtoexport = 0
				vertstoexport = 0
				
-- 				if mymesh.numverts > mymesh.numtverts then						
-- 				(						
-- 										numtoexport = mymesh.numverts
-- 										vertstoexport = 1
-- 									)
-- 									else
-- 									(
-- 										numtoexport = mymesh.numtverts
-- 										vertstoexport = 0
-- 									)--endif

				--put the faces into an array
					myfaces = #()
					mytexfaces = #()
			
						for f = 1 to  mymesh.numfaces do
									(
										myf = getface mymesh f
											append myfaces myf
										
										
										mytf = gettvface mymesh f
											append mytexfaces mytf
									) --next f
					
		--put the vertices into arrays
					myverts = #()
					mytverts = #()
					mynormals = #()
									
									--vertices
					for v = 1 to mymesh.numverts do
					(
						myvert = getvert mymesh v
						 append myverts myvert
				
						mynorm = getnormal mymesh v
						 append mynormals mynorm
						)
						
						--textures
					for t = 1 to mymesh.numtverts do
					(
						mytvert = gettvert mymesh t
						 append mytverts mytvert
						)

/* 							for v = 1 to myfaces.count do
* 							(
* 							-- 	insertItem <value> <array> <integer>
* 							-- Inserts the value at the specified index in the array, growing the array if necessary. Returns OK.
* 
* 									for g = 1 to 3 do (
* 										
* 												vertex =  in coordsys world getvert mymesh (myfaces[v][g])
* 												
* 												tvertex = gettvert mymesh (mytexfaces[v][g])
* 
* 												normal = getnormal mymesh (myfaces[v][g])
* 										
* -- 											placetoexport = mytexfaces[v][g]
* -- 												if vertstoexport == 1 then 
* -- 													( placetoexport = myfaces[v][g]) --endif
* 												
* 											placetoexport = myfaces[v][g]
* 												
* 											if placetoexport > myverts.count then 
* 												(
* 													insertitem vertex myverts placetoexport
* 													insertitem normal mynormals placetoexport
* 												
* 													insertitem tvertex mytverts placetoexport
* 											
* 												)
* 												else
* 												(
* 														myverts[ placetoexport] = vertex	
* 														mynormals[ placetoexport] = normal
* 														mytverts[ placetoexport ] = tvertex
* 												)--endif
* 													
* 										)--next g
* 
* 								)	--next v		
*/
					
			--get rid of temporary mesh	
				delete mymesh 
				delete emesh
								
		----write file
					vertcount = myverts.count --mymesh.numverts					
					normcount = mynormals.count * 3	
					facecount = myfaces.count --mymesh.numfaces		
					texcount = mytverts.count * 3			
								
								--vertices			
				format "% \n" (vertcount * 3) to:out
				
				for v = 1 to myverts.count do
					(
						vertex = myverts[v]
						
						format "% " (u * vertex.x) to:out
						format "% " (u * vertex.z ) to:out
						format "% " (u * (-1 * vertex.y)) to:out
			
								--writefloat out (u * vertex.x)
								--writefloat out (u * vertex.z )
								--writefloat out (u * (-1 * vertex.y))
						)--next v
				format "\n" to:out
								--normals				
				format "% \n" normcount to:out
			
					for n = 1 to mynormals.count do
					(
						normal = mynormals[n]
						
						format "% " (normal.x ) to:out
						format "% "  (normal.z ) to:out
						format "% "  (-1 * normal.y ) to:out
						
						--	writefloat out (normal.x )
						--writefloat out (normal.z )
 						--	writefloat out (-1 * normal.y )
						)--next n
					format "\n" to:out
						
								--texcoords
				format "% \n" texcount to:out
						
					for t = 1 to mytverts.count do
					(
						tex = mytverts[t]
						
						format "% " tex.x to:out
						format "% "  tex.y to:out
						format "0.0 " to:out  --the third one is not used in the format anyway
						
						--	writefloat out tex.x
 						--	writefloat out tex.y
						)--next t
						
					format "\n"	to:out
								
								--triangles			
				format "% \n" facecount to:out
						
						for i = 1 to facecount do
						(
							face = myfaces[i]
							tface = mytexfaces[i]
							
							--just a workaround -- so max wont export them as ex 0.0 but 0 instead etc.
							a = (face.x - 1) as integer
							b = (face.y - 1) as integer
							c = (face.z - 1) as integer
							
							d = (tface.x - 1) as integer
							ee = (tface.y - 1) as integer
							f = (tface.z - 1) as integer
							
							format "% " a #unsigned to:out
							format "% " a #unsigned to:out
							format "% " d #unsigned to:out
							
							format "% " b #unsigned to:out
							format "% " b #unsigned to:out
							format "% " ee #unsigned to:out
							
							format "% " c #unsigned to:out
							format "% " c #unsigned to:out
							format "% " f #unsigned to:out
							
							--	writelong out (face.x - 1) #unsigned
							--	writelong out (face.y - 1) #unsigned
							--	writelong out (face.z - 1) #unsigned
							
							)--next i
							
				format "\n"	to:out
		
		
		--numverts (actually export 3 * num of vertices)
		--verts
		
		--numnormals = 3 * numverts
		--normals
		
		--texcoords = 3 * triangles
		--texcoords
		
		--num triangles
		-- indexes vertex.x normal.x texcoord.x .. y y y ... z z z
		
		--end of the file -- these are not used but needed
			format "ambient 0.0 0.0 0.0 \n" to:out
			format "diffuse 1.0 1.0 1.0 \n" to:out
			format "specular 0.0 0.0 0.0 \n" to:out
	
			--close file
				close out
	)--function end
	

	
	--main
	output_name = getSaveFileName  caption:"Maxfile " types:"Dat (*.dat)|*.dat|All Files (*.*)|*.*|"
	
	if output_name !=undefined then 				
		(
		  exportTheModel output_name
		)--endif
		
