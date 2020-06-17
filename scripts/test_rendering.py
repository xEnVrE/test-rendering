import cv2
import numpy as np
import os
import sys
import trimesh

# Force rendering with EGL
os.environ["PYOPENGL_PLATFORM"] = "egl"
import pyrender

# Load the mesh
trimesh_mesh = trimesh.load(str(sys.argv[1]))
mesh = pyrender.Mesh.from_trimesh(trimesh_mesh)

# Create the scene
scene = pyrender.Scene(bg_color=[0.0, 0.0, 0.0])

# Insert the object
object_pose = np.array([
       [0.303053,-0.452284,  0.332065, 0.0],
       [0.545211, 0.0800298,-0.452284, 0.0],
       [0.132566, 0.545211,  0.303053,-0.3],
       [0.0,      0.0,       0.0,      1.0],
])
scene.add(mesh, pose=object_pose)


# Create and insert the camera
camera_width = 640
camera_height = 480
camera = pyrender.IntrinsicsCamera(fx=614.0, fy=614.0, cx=camera_width/2.0, cy=camera_height/2.0)
scene.add(camera)

# Create and insert the light
light = pyrender.SpotLight(color=np.ones(3), intensity=1.5, innerConeAngle=np.pi/16.0)
scene.add(light)

# Render the scene
renderer = pyrender.OffscreenRenderer(camera_width, camera_height)
render_rgb, render_depth = renderer.render(scene)

# Save the image
render_rgb = cv2.cvtColor(render_rgb, cv2.COLOR_RGB2BGR)
cv2.imwrite("./test-renderer_output.png", render_rgb)
