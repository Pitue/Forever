	const std::string root = "Media\\";
	
	int i = 0;
	std::vector<std::string> files;
	for (auto x : std::filesystem::recursive_directory_iterator(root, std::filesystem::directory_options::skip_permission_denied)) {
		if (x.is_directory()) continue;
		if (x.is_regular_file()) {
			if (x.path().extension() == ".png") {
				files.push_back("textures[" + std::to_string(i) + "] = \"" + x.path().u8string() + "\";");
				i++;
				for (auto& c : files.back()) {
					if (c == '\\') c = '/';
				}
			}
		}
	}

	std::fstream file;
	file.open("n.txt", std::ios::out | std::ios::trunc);
	for (auto& x : files) {
		file << x << '\n';
	}
	file.close();

	std::vector<std::string> names;
	for (auto x : std::filesystem::recursive_directory_iterator(root, std::filesystem::directory_options::skip_permission_denied)) {
		if (x.is_regular_file()) {
			if (x.path().extension() == ".png") {
				std::string t = x.path().filename().string(); t.resize(t.length() - x.path().extension().string().length());
				for (auto& c : t) {
					if (c >= 'a' && c <= 'z') c -= 'a' - 'A';
				}
				names.push_back(t);
			}
		}
	}
	std::fstream file;
	file.open("n.txt", std::ios::out | std::ios::trunc);
	for (auto& x : names) {
		file << x << ",\n";
	}
	file.close();

	return 0;