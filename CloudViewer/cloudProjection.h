#ifndef CLOUDPROJECTION_H
#define CLOUDPROJECTION_H

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/transforms.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QDebug>

#include "./ui_mainwindow.h"

class cloudProjecter
{
public:
    int cloud_size = 0;
    pcl::PointCloud<pcl::PointXYZI>::Ptr pc;
public:
    cloudProjecter()
    {
        pc.reset(new pcl::PointCloud<pcl::PointXYZI>());
    }

    void readPointCloud(std::string fileName)
    {
        if (fileName.length() < 5)
        {
            return;
        }

        if (fileName.substr(fileName.length() - 4, 4) == ".bin" || fileName.substr(fileName.length() - 4, 4) == ".BIN")
        {
            if (pcl::io::loadPCDFile<pcl::PointXYZI>(fileName, *pc) != 0)
            {
                return;
            }
        }
        else if (fileName.substr(fileName.length() - 4, 4) == ".pcd" || fileName.substr(fileName.length() - 4, 4) == ".PCD")
        {
            if (pcl::io::loadPCDFile<pcl::PointXYZI>(fileName, *pc) != 0)
            {
                return;
            }
        }
        else if (fileName.substr(fileName.length() - 4, 4) == ".ply" || fileName.substr(fileName.length() - 4, 4) == ".PLY")
        {
            if (pcl::io::loadPLYFile<pcl::PointXYZI>(fileName, *pc) != 0)
            {
                return;
            }
        }

        cloud_size = pc->size();
    }

    QImage getImage(int width = 730, double scale = 1.0, int r=0, int g=0, int b=0)
    {
        QImage image(width, width, QImage::Format_RGB888);
        image.setColorCount(256);
        image.fill(qRgb(r, g, b));
        for(int i=0; i<cloud_size; i++)
        {
            int x = std::min(std::max(0, int(pc->points[i].x*scale+width/2)), width-1);
            int y = std::min(std::max(0, int(pc->points[i].y*scale+width/2)), width-1);

            image.setPixelColor(x, y, qRgb(pc->points[i].z, 0, 255));
        }

        return image;
    }


};

#endif // CLOUDPROJECTION_H
