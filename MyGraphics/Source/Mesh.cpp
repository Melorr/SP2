#include "Mesh.h"
#include "GL\glew.h"
#include "Vertex.h"

/******************************************************************************/
/*!
\brief
Default constructor - generate VBO/IBO here

\param meshName - name of mesh
*/
/******************************************************************************/
Mesh::Mesh(const std::string &meshName)
	: name(meshName)
	, mode(DRAW_TRIANGLES)
    , textureID(0)
{
    // Generate buffers
    glGenBuffers(1, &indexBuffer);
    glGenBuffers(1, &vertexBuffer);
}

/******************************************************************************/
/*!
\brief
Destructor - delete VBO/IBO here
*/
/******************************************************************************/
Mesh::~Mesh()
{
    if (textureID > 0) {
        glDeleteTextures(1, &textureID);
    }

    // Cleanup VBO here
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
}

/******************************************************************************/
/*!
\brief
OpenGL render code
*/
/******************************************************************************/
void Mesh::Render()
{
    glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
    glEnableVertexAttribArray(1); // 2nd attribute buffer : colors
    glEnableVertexAttribArray(2); // 3rd attrivute buffer : normals
    if (textureID > 0) {
        glEnableVertexAttribArray(3);

    }

    //Render call setup
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
    if (textureID > 0) {
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (void*)(sizeof(Position)+sizeof(Color)+sizeof(Vector3)));
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    //Actual render call
    if (mode == DRAW_TRIANGLE_STRIP) {
        glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0);
    }
    else if (mode == DRAW_LINES) {
        glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);
    }
    else if (mode == DRAW_TRIANGLE_FAN) {
        glDrawElements(GL_TRIANGLE_FAN, indexSize, GL_UNSIGNED_INT, 0);
    }
	else {
		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
	}


    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    //Add these codes before end of method
    if (textureID > 0) {
        glDisableVertexAttribArray(3);
    }
}

void Mesh::Render(unsigned offset, unsigned count) 
{
    glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
    glEnableVertexAttribArray(1); // 2nd attribute buffer : colors
    glEnableVertexAttribArray(2); // 3rd attrivute buffer : normals
    if (textureID > 0) {
        glEnableVertexAttribArray(3);

    }

    //Render call setup
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position)+sizeof(Color)));
    if (textureID > 0) {
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (void*)(sizeof(Position)+sizeof(Color)+sizeof(Vector3)));
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    //Actual render call
    if (mode == DRAW_LINES) {
        glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
    }
    else if (mode == DRAW_TRIANGLE_STRIP) {
        glDrawElements(GL_TRIANGLE_STRIP, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
    }
    else {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    //Add these codes before end of method
    if (textureID > 0) {
        glDisableVertexAttribArray(3);
    }
}