#pragma once
#include "node.hpp"

// Node3D: Contains 3D tranformations.
// Such as: position, rotation, scale, and skew.
struct Node3D : public Node {
	/// @brief Construct a Node3D object from an existing in-scope Node object.
	/// @param addr The address of the Node3D object.
	Node3D(uint64_t addr) : Node(addr) {}

	/// @brief Construct a Node3D object from a path.
	/// @param path The path to the Node3D object.
	Node3D(const std::string& path) : Node(path) {}

	/// @brief Get the position of the node.
	/// @return The position of the node.
	Vector3 get_position() const;
	/// @brief Set the position of the node.
	/// @param value The new position of the node.
	void set_position(const Variant &value);

	/// @brief Get the rotation of the node.
	/// @return The rotation of the node.
	Vector3 get_rotation() const;
	/// @brief Set the rotation of the node.
	/// @param value The new rotation of the node.
	void set_rotation(const Variant &value);

	/// @brief Get the scale of the node.
	/// @return The scale of the node.
	Vector3 get_scale() const;
	/// @brief Set the scale of the node.
	/// @param value The new scale of the node.
	void set_scale(const Variant &value);

	// TODO:
	// void set_transform(const Transform3D &value);
	// Transform3D get_transform() const;
	// void set_quaternion(const Quaternion &value);
	// Quaternion get_quaternion() const;

	/// @brief  Duplicate the node.
	/// @return A new Node3D object with the same properties and children.
	Node3D duplicate() const;
};

inline Node3D Variant::as_node3d() const {
	if (get_type() == Variant::OBJECT)
		return Node3D{uintptr_t(v.i)};
	else if (get_type() == Variant::NODE_PATH)
		return Node3D{*v.s};

	api_throw("std::bad_cast", "Variant is not a Node3D or NodePath", this);
}
