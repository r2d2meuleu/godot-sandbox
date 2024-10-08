#pragma once

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>

struct Docker {
	using Array = godot::Array;
	using PackedStringArray = godot::PackedStringArray;
	using String = godot::String;

	static bool ContainerStart(String container_name, String image_name, Array &output);
	static Array ContainerStop(String container_name);
	static bool ContainerExecute(String container_name, const PackedStringArray &args, Array &output);

	static String GetFolderName(const String &path) {
		String foldername = path.replace("res://", "");
		int idx = -1;
		do {
			idx = foldername.find("/");
			if (idx != -1)
				foldername = foldername.substr(idx + 1, foldername.length());
		} while (idx != -1);
		return foldername;
	}
};
