#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>

GLuint VBO;//назначаем GLuint в качестве глобальной переменной для хранения указателя на буфер вершин
static void RenderSceneCB() // очищает буфер цвета
{
	glClear(GL_COLOR_BUFFER_BIT);//очистка буфера кадра
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);// привязываем наш буфер, приготавливая его для отрисовки

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//Первый параметр указывает на индекс атрибута.Второй-количество компонентов в атрибуте (3 для X, Y и Z).Третий параметр - тип данных для каждого компонента.4-данные передаются не именными.5-число байтов между 2 экземплярами атрибута.

	glDrawArrays(GL_TRIANGLES, 0, 3);// функцию для отрисовки

	glDisableVertexAttribArray(0);// отключает каждый атрибут вершины, как только отпадает необходимость
	glutSwapBuffers();//меняет фоновый буфер и буфер кадра местами
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(1024, 768); // размер
	glutInitWindowPosition(100, 100); // позиция на экране
	glutCreateWindow("Tutorial 01"); // названия окна

	glutDisplayFunc(RenderSceneCB); // регулярно вызывает рендер сцену

	glClearColor(1.0f, 0.0f, 0.9f, 0.0f); // цвет бг


	GLenum res = glewInit();//мы инициализируем GLEW и проверяем на ошибки.
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glm::vec3 Vertices[3];//задаем координаты 
	Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
	Vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
	Vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);


	glGenBuffers(1, &VBO);//первый определяет количество объектов,второй ссылка на массив типа GLuints для хранения указателя

	glBindBuffer(GL_ARRAY_BUFFER, VBO);// связываем буффер вершин с указателем вершин

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glutMainLoop(); // цикл вызывающий дисплей фанк, чтобы дать ей возможность нарисовать кадр



}
