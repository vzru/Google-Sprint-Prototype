#include "Material.h"
#include <iostream>

Material::Material()
{

}

Material::Material(std::string diffusePath, std::string specularPath, float specExp, glm::vec3 & hue)
	: specularExponent(specExp), hue(hue)
{
	loadTexture(TextureType::Diffuse, diffusePath);
	loadTexture(TextureType::Specular, specularPath);
	loadTexture(TextureType::Normal, specularPath);
}

Material::~Material()
{

}

void Material::loadTexture(TextureType type, std::string texFile)
{
	switch (type)
	{
	case Diffuse:
		if (!diffuse.load(texFile))
		{
			system("pause");
			exit(0);
		}
		break;
	case Specular:
		if (!specular.load(texFile))
		{
			system("pause");
			exit(0);
		}
		break;
	case Normal:
		if (!normal.load(texFile))
		{
			system("pause");
			exit(0);
		}
		break;
	default:
	{
		std::cout << "Error - TextureType not found: " << std::endl;
		system("pause");
		exit(0);
	}
		break;
	}
}
