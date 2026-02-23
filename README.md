
---

````markdown
# PCD Transformation Tool

A lightweight C++ tool for applying rigid body transformations  
(rotation + translation) to PCD point cloud files.

The transformation parameters are configured via a YAML file.

---

## Features

- Rotate around Z axis (yaw)
- Translate in X / Y / Z directions
- Configurable via `config.yaml`
- Binary PCD output
- Based on:
  - PCL 1.12
  - Eigen
  - yaml-cpp

---

## Dependencies

Ubuntu 22.04:

```bash
sudo apt update
sudo apt install libpcl-dev
sudo apt install libyaml-cpp-dev
````

---

## Build

```bash
mkdir build
cd build
cmake ..
make
```

The executable will be generated in:

```
build/rotate
```

---

## Usage

```bash
./rotate config.yaml
```

---

## Example config.yaml

```yaml
input_pcd: "./data/pointcloud_map.pcd"
output_pcd: "./data/transformed/map_transformed.pcd"

rotation_deg: 0.0

translation:
  x: 0.0
  y: 0.0
  z: 0.0
```

---

## Transformation Model

The tool applies a rigid body transform:

```
p' = R * p + t
```

Where:

* R = rotation around Z axis
* t = translation vector (x, y, z)

Rotation follows right-hand rule:

* Positive angle → Counterclockwise
* Negative angle → Clockwise

---

## Coordinate Convention

* X: forward
* Y: left
* Z: up

Right-handed coordinate system (PCL default).

---

## Notes

* Rotation is applied around origin (0,0,0).
* Translation is applied after rotation.
* Output is saved in binary PCD format.

---

## Typical Use Cases

* Map yaw correction
* Global map alignment
* GNSS / local frame adjustment
* Manual map calibration

---

## Author

Custom internal tool for point cloud transformation - TCAV team
