#include "AssimpLoader.h"
using namespace std;
#include <iostream>
#include "OpenglUtils.h"
#include <glm/glm.hpp>


namespace AssimpLoader
{

	//Extracts all the data we need and puts into into our parameters
	void loadObjectData(const std::string& file, vector<int>& meshIDs, vector<int>& indexCount, vector<glm::vec3>& maxmin)
	{
	
		// Create an instance of the Importer class for loading the object data
		Assimp::Importer importer;


		//loads our file into a scene object so its all accessible.
		const aiScene* scene = importer.ReadFile(file,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_FlipUVs |
			aiProcess_SortByPType
			//aiProcess_FixInfacingNormals  
		//	| aiProcess_FindInvalidData
			//| aiProcess_RemoveComponent
			| aiProcess_GenSmoothNormals 
			//| aiProcess_FindDegenerates
			//| aiProcess_PreTransformVertices
			|aiProcess_GenNormals

		);

			//  | aiProcess_JoinIdenticalVertices		

		if (!scene)
		{
			std::cout << "ERROR: Assimp file load failed." << std::endl;
			const char * 	GetErrorString();
		
		}

		//these store the minimum and maxium vertices for object
		glm::vec3 min(1000, 1000, 1000);
		glm::vec3 max(-1000, -1000, -1000);

		

		const aiMesh* mesh;
		//cout << "Number of meshes: " << scene->mNumMeshes << endl;


		//Temporary containers for object data
		std::vector<float> verts;
		std::vector<float> norms;
		std::vector<float> texCoords;
		std::vector<int>   indices;
		std::vector<float> colours;

		//will store the mesh ID of each scene mesh after they have been individually sent to openglUtils.
		//vector<int> meshIDs;
		
		int texCount = 0;

		for (unsigned int j = 0; j < scene->mNumMeshes; j++)
		{
			mesh = scene->mMeshes[j];
			int numOfFaces = mesh->mNumFaces;
			int numOfIndices = numOfFaces * 3;


			for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
				const aiFace &face = mesh->mFaces[i];
				indices.push_back(face.mIndices[0]);
				indices.push_back(face.mIndices[1]);
				indices.push_back(face.mIndices[2]);		

			}

			int numOfVertices = mesh->mNumVertices;

			for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
				if (mesh->HasPositions()) {
					verts.push_back(mesh->mVertices[i].x);
					verts.push_back(mesh->mVertices[i].y);
					verts.push_back(mesh->mVertices[i].z);

					//Stores the min and mex vertices
					if (mesh->mVertices[i].x < min.x)   min.x = mesh->mVertices[i].x;
					if (mesh->mVertices[i].y < min.y)   min.y = mesh->mVertices[i].y;
					if (mesh->mVertices[i].z < min.z) 	min.z = mesh->mVertices[i].z;
					
					if (mesh->mVertices[i].x > max.x) 	max.x = mesh->mVertices[i].x;
					if (mesh->mVertices[i].y > max.y) 	max.y = mesh->mVertices[i].y;
					if (mesh->mVertices[i].z > max.z)   max.z = mesh->mVertices[i].z;
							
				}

				if (mesh->HasNormals()) {
					norms.push_back(mesh->mNormals[i].x);
					norms.push_back(mesh->mNormals[i].x);
					norms.push_back(mesh->mNormals[i].x);

				}

				if (mesh->HasTextureCoords(0)) {
					texCoords.push_back(mesh->mTextureCoords[0][i].x);
					texCoords.push_back(mesh->mTextureCoords[0][i].y);

					texCount += 2;

				}

				if (mesh->HasVertexColors(0)) {
					colours.push_back(mesh->mColors[j][i].r);
					colours.push_back(mesh->mColors[j][i].g);
					colours.push_back(mesh->mColors[j][i].b);

				}
			}

			//cout << texCount << endl;
			int ID = OpenglUtils::createMesh((GLuint)verts.size(), (GLfloat*)verts.data(), (GLfloat*)colours.data(), (GLfloat*)norms.data(), (GLfloat*)texCoords.data(), (GLuint)texCoords.size(), (GLuint)indices.size(), (GLuint*)indices.data());
			meshIDs.push_back(ID);
			indexCount.push_back(indices.size());

			

			colours.clear(); norms.clear(); texCoords.clear(); verts.clear(); indices.clear();

		}
	

		//Pass out min and max
		maxmin.push_back(min);
		maxmin.push_back(max);

	}


	

}