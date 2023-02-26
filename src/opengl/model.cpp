#include <iostream>
#include <unordered_map>
#include <tinyobjloader/tiny_obj_loader.h>
#include <STB_IMAGE/stb_image.h>
#include "opengl/model.h"
#include "opengl/texture2d.h"

Model::Model(const std::string& p_filename, const std::string& p_directory)
{
    // TODO: clean this up and split into separate functions
    
    // Load the object
    std::cout << "Loading object : " << p_filename << std::endl;
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = p_directory;

    tinyobj::ObjReader objReader;

    if(!objReader.ParseFromFile(p_filename, reader_config))
    {
        if(!objReader.Error().empty())
        {
            std::cout << "ERROR : " << objReader.Error() << std::endl;
            return;
        }
    }

    if(!objReader.Warning().empty())
    {
        std::cout << "WARNING : " << objReader.Warning();
    }

    auto& attrib = objReader.GetAttrib();
    auto& shapes = objReader.GetShapes();
    auto& materials = objReader.GetMaterials();
    std::cout << "- Loaded " << shapes.size() << " shapes, " << materials.size() << " materials from " << p_filename << std::endl;

    
    // Loop through the shapes and create meshes
    // Need vertices, indices and textures
    for(const auto& shape : shapes)
    {
        std::cout << "- Processing shape : " << shape.name << std::endl;
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;
        std::unordered_map<Vertex, int> uniqueVertices;

        for(const auto& index: shape.mesh.indices)
        {
            Vertex vertex;
            glm::vec3 vector;

            // Positions
            vector.x = attrib.vertices[3 * index.vertex_index + 0];
            vector.y = attrib.vertices[3 * index.vertex_index + 1];
            vector.z = attrib.vertices[3 * index.vertex_index + 2];
            vertex.position = vector;

            // Normal index
            if(index.normal_index >= 0)
            {
                vector.x = attrib.normals[3 * index.normal_index + 0];
                vector.y = attrib.normals[3 * index.normal_index + 1];
                vector.z = attrib.normals[3 * index.normal_index + 2];
                vertex.normal = vector;
            }
            
            // Texture coordinates
            if(index.texcoord_index >= 0)
            {
                glm::vec2 vec;
                vec.x = attrib.texcoords[2 * index.texcoord_index + 0];
                vec.y = attrib.texcoords[2 * index.texcoord_index + 1];
                vertex.texCoords = vec;
            }
            else
            {
                vertex.texCoords = glm::vec2(0.0f, 0.0f);
            }

            // TODO: calculate tangent and bitangent
            // Tangents
            vertex.tangent = glm::vec3(0, 0, 0);

            // Bi-tangent
            vertex.bitangent = glm::vec3(0, 0, 0);

            if(uniqueVertices.count(vertex) == 0)
            {
                uniqueVertices[vertex] = vertices.size();
                vertices.push_back(vertex);
            }
            
            indices.push_back(GLuint(uniqueVertices[vertex]));
        }
        
        // Find the material name corresponding to this shape
        int matIndex = shape.mesh.material_ids[0];

        std::cout << "-- Alpha texture name : " << materials[matIndex].alpha_texname << std::endl;

        if(matIndex >= 0)
        {
            int textureSlot = 0;
            if(!materials[matIndex].diffuse_texname.empty())
            {
                std::cout << "-- Loading DIFFUSE texture : " << materials[matIndex].diffuse_texname << std::endl;
                textures.push_back(this->loadMaterialTexture(p_directory + materials[matIndex].diffuse_texname, "albedoMap"));
            }
            if(!materials[matIndex].specular_texname.empty())
            {
                std::cout << "-- Loading SPECULAR texture : " << materials[matIndex].specular_texname << std::endl;
                textures.push_back(this->loadMaterialTexture(p_directory + materials[matIndex].diffuse_texname, "specularMap"));
            }
            if(!materials[matIndex].bump_texname.empty())
            {
                std::cout << "-- Loading NORMAL texture : " << materials[matIndex].bump_texname << std::endl;
                textures.push_back(this->loadMaterialTexture(p_directory + materials[matIndex].diffuse_texname, "normalMap"));
            }
            if(!materials[matIndex].alpha_texname.empty())
            {
                std::cout << "-- Loading ALPHA texture : " << materials[matIndex].alpha_texname << std::endl;
                textures.push_back(this->loadMaterialTexture(p_directory + materials[matIndex].diffuse_texname, "alphaMap"));
            }
        }

        // Add mesh
        this->meshes.push_back(Mesh(vertices, indices, textures));
    }

}

Texture Model::loadMaterialTexture(const std::string& p_path, const std::string& p_typeName)
{
    Texture texture;
    Texture2D tex2d(p_path, 0);
    texture.id = tex2d.textureID;
    texture.type = p_typeName;
    texture.path = p_path;

    return texture;
}

void Model::draw(Program& p_program)
{
    for(GLuint i = 0; i < this->meshes.size(); i++)
    {
        this->meshes[i].draw(p_program);
    }
}

