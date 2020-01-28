//#include "funset.hpp"
#include <iostream>
#include <Python.h> 
//It contains various macro declarations that are later used to #include the
//appropriate public FreeType 2 header files.
#include <ft2build.h>
//FT_FREETYPE_H is a special macro defined in file ftheader.h. It contains some
//installation-specific macros to name other public header files of the FreeType 2 API.
#include FT_FREETYPE_H
#include <ftglyph.h>
 
#include <opencv2/opencv.hpp>
 
#include "CvxText.hpp"
 
int putTextCN(
	char * im_file, 
	char * font, 
	double char_size,
    double char_interval,	
	int x, 
	int y, 
	char * raw_text)
{
	cv::Mat mat = cv::imread(im_file, 1);
	if (!mat.data || mat.channels() != 3) {
		fprintf(stderr, "read image fail\n");
		return -1;
	}

    CvxText text(font); //指定字体
	cv::Scalar size{char_size, 0, char_interval, 0};
	text.setFont(nullptr, &size, nullptr, 0);
	text.putText(mat, raw_text, cv::Point(x, y), cv::Scalar(255, 0, 0));
	/*
	cv::Scalar size1{ 100, 0.5, 0.1, 0 }, size2{ 100, 0, 0.1, 0 }, size3{ 50, 0, 1, 0 }, size4{50, 0, 0.1, 0}; // (字体大小, 无效的, 字符间距, 无效的 }
 
	text.setFont(nullptr, &size1, nullptr, 0);
	text.putText(mat, "中国", cv::Point(50, 100));
 
	text.setFont(nullptr, &size2, nullptr, 0);
	text.putText(mat, "北京", cv::Point(50, 200), cv::Scalar(255, 0, 0));
 
	text.setFont(nullptr, &size3, nullptr, 0);
	text.putText(mat, "China", cv::Point(50, 250), cv::Scalar(0, 255, 0));
 
	text.setFont(nullptr, &size4, nullptr, 0);
	text.putText(mat, "BeiJing", cv::Point(50, 300), cv::Scalar(0, 0, 255));
    */
	cv::imwrite("new.png", mat);
 
	return 0;
}

static PyObject * _putTextCN(PyObject *self, PyObject *args) //, PyObject *kwargs)
{
    char * im_file;
	char * font;
	double char_size;
	double char_interval;
	int x;
	int y;
	char * raw_text;

    static char *kwlist[] = {
		"im_file", "font", "char_size", "char_interval", "x", "y", "raw_text", NULL};

	if (!PyArg_ParseTupleAndKeywords(args, NULL, "ssddiis", kwlist, &im_file, &font, &char_size, &char_interval, &x, &y, &raw_text)) {
		return NULL;
	}

    int res;

	res = putTextCN(im_file, font, char_size, char_interval, x, y, raw_text);
    return Py_BuildValue("i", res);
}

static PyMethodDef OpenCVputTextSupportCN[] = {
	{"putTextCN", _putTextCN, METH_VARARGS | METH_KEYWORDS, },
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef opencv_puttext_support_cn_module = {
	PyModuleDef_HEAD_INIT,
	"opencv_puttext_support_cn",
	"A putText module support CN",
	-1,
	OpenCVputTextSupportCN
};

PyMODINIT_FUNC PyInit_opencv_puttext_support_cn() {
	return PyModule_Create(&opencv_puttext_support_cn_module);
}

/*
int main(int argc, char *argv[])
{
    char * file;
    char * font;
	//char * text;
	file = argv[1];
	font = argv[2];
    //text = "北京";

	putTextCN(file, font, 50, 0.2, 100, 100, "安检的图片");
}
*/
