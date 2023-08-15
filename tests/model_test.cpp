//#include <catch2/catch_test_macros.hpp>
//#include <catch2/benchmark/catch_benchmark.hpp>
//
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//
//
//#include <iostream>
//
//#include <snjModel.h>
//
//TEST_CASE("MODEL_TEST")
//{
//	Assimp::Importer importer;
//
//	std::string path = "cube.obj";
//
//	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//	bool success;
//
//	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//	{
//		std::cout << importer.GetErrorString() << std::endl;
//		success = false;
//	}
//	else
//		success = true;
//
//	REQUIRE(success == true);
//
//	unsigned int num_of_meshes = scene->mNumMeshes;
//	
//	// For every mesh
//	for (int mesh_index = 0; mesh_index < num_of_meshes; ++mesh_index)
//	{
//		//snjModel("fdsfsdf").__processMesh(scene->mMeshes[mesh_index], scene);
//		snjModel model_1("cube.obj");
//
//		unsigned int num_of_vertices = scene->mMeshes[mesh_index]->mNumVertices;
//		std::cout << "num_of_vertices = " << num_of_vertices << " in mesh = " << mesh_index << std::endl;
//
//		for (size_t vertex_index = 0; vertex_index < num_of_vertices; ++vertex_index)
//		{
//			
//			float vertex_x = scene->mMeshes[mesh_index]->mVertices[vertex_index].x;
//			float vertex_y = scene->mMeshes[mesh_index]->mVertices[vertex_index].y;
//			float vertex_z = scene->mMeshes[mesh_index]->mVertices[vertex_index].z;
//
//			std::cout << "(" << vertex_x << ", " << vertex_y << ", " << vertex_z << ") " << std::endl;
//		}
//
//		unsigned int num_of_faces = scene->mMeshes[mesh_index]->mNumFaces;
//
//		// for each face read indices
//		for (int face_index = 0; face_index < num_of_faces; ++face_index)
//		{
//			unsigned int num_of_indices = scene->mMeshes[mesh_index]->mFaces[face_index].mNumIndices;
//			std::cout << "face #" << face_index << " = { ";
//
//			// for each indices
//			for (int index_index = 0; index_index < num_of_indices; ++index_index)
//			{
//				std::cout << scene->mMeshes[mesh_index]->mFaces[face_index].mIndices[index_index] << " ";
//			}
//			std::cout << "}" << std::endl;
//
//
//
//		}
//		
//		std::cout << "Normals" << std::endl;
//
//		unsigned int num_of_normals = scene->mMeshes[mesh_index]->mNumVertices;
//
//		for (size_t normal_index = 0; normal_index < num_of_normals; ++normal_index)
//		{
//			float normal_x = scene->mMeshes[mesh_index]->mNormals[normal_index].x;
//			float normal_y = scene->mMeshes[mesh_index]->mNormals[normal_index].y;
//			float normal_z = scene->mMeshes[mesh_index]->mNormals[normal_index].z;
//
//			std::cout << "#" << normal_index << "(" << normal_x << ", " << normal_y << ", " << normal_z << ")" << std::endl;
//		}
//
//		//scene->mMeshes[mesh_index].
//
//
//
//
//	}
//
//
//
//
//
//}