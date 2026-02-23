#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/transforms.h>
#include <pcl/console/print.h>
#include <Eigen/Dense>
#include <yaml-cpp/yaml.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: ./rotate config.yaml\n";
        return -1;
    }

    std::string config_file = argv[1];

    // ================= Read YAML =================
    YAML::Node config = YAML::LoadFile(config_file);

    std::string input_pcd  = config["input_pcd"].as<std::string>();
    std::string output_pcd = config["output_pcd"].as<std::string>();

    double angle_deg = config["rotation_deg"].as<double>();

    float tx = config["translation"]["x"].as<float>();
    float ty = config["translation"]["y"].as<float>();
    float tz = config["translation"]["z"].as<float>();

    // ================= Read PCD =================
    pcl::PointCloud<pcl::PointXYZ>::Ptr source(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::PointCloud<pcl::PointXYZ>::Ptr transformed(new pcl::PointCloud<pcl::PointXYZ>());

    if (pcl::io::loadPCDFile<pcl::PointXYZ>(input_pcd, *source) != 0)
    {
        pcl::console::print_error("ERROR: Failed to load PCD file: %s\n", input_pcd.c_str());
        return -1;
    }

    pcl::console::print_info("Loaded successfully. Total points: %d\n", source->size());

    // ================= Build transformation matrix =================
    Eigen::Matrix4f transform = Eigen::Matrix4f::Identity();

    float rad = angle_deg * M_PI / 180.0f;

    // Rotation around Z axis
    transform(0,0) =  cos(rad);
    transform(0,1) = -sin(rad);
    transform(1,0) =  sin(rad);
    transform(1,1) =  cos(rad);

    // Translation
    transform(0,3) = tx;
    transform(1,3) = ty;
    transform(2,3) = tz;

    // ================= Apply transformation =================
    pcl::transformPointCloud(*source, *transformed, transform);

    pcl::console::print_info("Applied transformation: Rotation %.2f deg, Translation (%.2f, %.2f, %.2f)\n",
                             angle_deg, tx, ty, tz);

    // ================= Save =================
    if (pcl::io::savePCDFileBinary(output_pcd, *transformed) == 0)
        pcl::console::print_info("Saved successfully to: %s\n", output_pcd.c_str());
    else
        pcl::console::print_error("ERROR: Failed to save output file.\n");

    return 0;
}