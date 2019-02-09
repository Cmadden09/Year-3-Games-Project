#ifndef MESHCOMPONENT
#define MESHCOMPONENT

#include <glm/glm.hpp>
#include <vector>
#include "Component.h"
#include "RenderingSystem.h"
using namespace std;


class MeshComponent : public Component
{
public:
	MeshComponent(std::string name);
	~MeshComponent() {}

	void init();
	void update(double dt);

	
	void loadTexture(char * filename);
	void loadObject(const char * filename);

	//Gets
	glm::vec3 getTranslation();
	glm::vec3 getScaling();
	glm::vec3 getRotate();
	int getMeshID();

	int getMeshIndexCount();
	int getTexcoordCount();
	int getTextureID();

	//Sets
	void setMesh(int ID) { meshID = ID; }
	void addTexture(int ID) { textures.push_back(ID); }
	void setRenderer(RenderingSystem* rendersystem);
	void setTranslation(glm::vec3 tran);
	void setScaling(glm::vec3 scale);

	void setMinMax(vector<glm::vec3> minmax);
	

	void setMeshes(vector<int> meshIDs);
	vector<int> getMeshes();

	vector<int> getTextures();

	float getRenderRotateDeg() { return deg; }


	

	void setIndexCounts(vector<int> indexCounts);
	vector<int> getIndexCounts();

	RenderingSystem *renderer;
private:
	//transformation data for renderer
	glm::vec3 translation;
	glm::vec3 scaling;
	glm::vec3 rotate;
	float deg;


	vector<int> meshIDs;
	vector<int> indexCounts;
	vector<int> textures;


	int vertCount;
	int meshIndexCount;
	int texCoordCount;

	int meshID;
	int textureID;
	//int material...


	

};
#endif