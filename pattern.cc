#include <iostream>
#include <cstdlib>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>

double ratio =1/2.0;
int iter = 100000;
int scale = 1000;

void cloudViewer(pcl::PointCloud<pcl::PointXYZ>::Ptr to_show) {
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("viewer"));
    viewer->setBackgroundColor (0, 0, 0);
    viewer->addCoordinateSystem (1.0f);
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> h1(to_show, 255, 255, 255);
    viewer->addPointCloud(to_show, h1, "h1");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "h1");
    while(!viewer->wasStopped()){
        viewer->spinOnce(100);
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));

    double x[6] = {1, 1, 1+0.86602, 1+2*0.86602, 1+2*0.86602, 1+0.86602};
    double y[6] = {0, 1, 1.5, 1, 0, -0.5};
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    for (int i = 0; i < 6; i++) {
        pcl::PointXYZ pt;
        pt.x = x[i]*scale;
        pt.y = y[i]*scale;
        pt.z = 0;
        cloud->points.push_back(pt);
    }

    int prev_anchor = 0;
    pcl::PointXYZ prev_pt;
    prev_pt = cloud->points[0];
    pcl::PointCloud<pcl::PointXYZ>::Ptr pattern (new pcl::PointCloud<pcl::PointXYZ>());
    while (iter--) {
        int anchor = prev_anchor;
        while (anchor == prev_anchor) {
            anchor = rand() % 6;
        }

        pcl::PointXYZ new_pt;
        new_pt.x = prev_pt.x + (cloud->points[anchor].x - prev_pt.x)*ratio;
        new_pt.y = prev_pt.y + (cloud->points[anchor].y - prev_pt.y)*ratio;
        pattern->points.push_back(new_pt);
        prev_pt = new_pt;
        prev_anchor = anchor;
    }


    cloudViewer(pattern);

    return 0;
}