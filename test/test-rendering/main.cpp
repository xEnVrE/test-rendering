/*
 * Copyright (C) 2020 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * GPL-2+ license. See the accompanying LICENSE file for details.
 */

#include <SuperimposeMesh/SICAD.h>

#include <opencv2/opencv.hpp>

#include <cstdlib>
#include <iostream>


int main(int argc, char** argv)
{
    const std::string log_name{argv[0]};

    if (argc != 3)
    {
        std::cerr << "Synopsis: " << log_name << " <mesh_path> <ground_truth_path>" << std::endl;

        return EXIT_FAILURE;
    }

    /* Mesh path. */
    SICAD::ModelPathContainer model_path;
    model_path["object"] = std::string{argv[1]};

    /* Camera parameters. */
    int width = 640;
    int height = 480;
    double fx = 614.0;
    double fy = fx;
    double cx = width / 2.0;
    double cy = height / 2.0;

    /* Renderer. */
    SICAD renderer(model_path, width, height, fx, fy, cx, cy, 1);

    /* Test pose. */
    SICAD::ModelPose pose;
    SICAD::ModelPoseContainer pose_container;
    pose.push_back(0.0);  // x
    pose.push_back(0.0);  // y
    pose.push_back(-0.5); // z
    pose.push_back(0.5);  // axis x
    pose.push_back(0.1);  // axis y
    pose.push_back(0.5);  // axis z
    pose.push_back(1.5);  // angle
    pose_container.emplace("object", pose);

    /* Camera pose placeholder. */
    double cam_x [4] = {0.0, 0.0, 0.0};
    double cam_o [4] = {1.0, 0.0, 0.0, 0.0};

    /* Render scene. */
    cv::Mat render;
    bool outcome = renderer.superimpose(pose_container, cam_x, cam_o, render);

    if (!outcome)
    {
        std::cerr << log_name << "::main. Error: error while trying to render the image." << std::endl;

        return EXIT_FAILURE;
    }

    cv::cvtColor(render, render, cv::COLOR_RGB2BGR);

    /* Save to file. */
    cv::imwrite("./test-renderer_output.png", render);

    return EXIT_SUCCESS;
}
