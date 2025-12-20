# Can-Bus-Manager

![C++ Qt CI](https://github.com/Can-Bus-Manager/Can-Bus-Manager/actions/workflows/ci.yml/badge.svg)

#### **Core Tools**
- **CMake ≥ 3.16**: Project configuration.
- **Ninja**: Fast build generator (used in Dev Mode).
- **C++17 Compiler**: `g++` or `clang` (installed via `build-essential`).
- **Qt 6.7.3+**: Required modules: `qt6-base-dev`, `qt6-tools-dev`.

#### **Documentation & Testing**
- **Doxygen & Graphviz**: For generating API documentation and diagrams.
- **QtTest**: Included with Qt development libraries.

#### **IDE (Optional)**
- **CLion** (Recommended for WSL integration) or **VS Code**.


## Quick Start

####  Quick Install 
Run this command to install all dependencies at once:
```bash
sudo apt update && sudo apt install -y build-essential cmake clang-tidy clang-format ninja-build qt6-base-dev qt6-tools-dev qt6-tools-dev-tools doxygen graphviz lcov
```
The project uses a unified control script to manage the build pipeline. Ensure the script is executable before first use:
`chmod +x start.sh`

### Common Commands

| Goal | Command |
|:--- |:--- |
| **Standard Run** | `./start.sh` |
| **Fast Dev Build** | `./start.sh -d` |
| **Clean Rebuild** | `./start.sh -c` |
| **Quick Launch** | `./start.sh -nt -nd` |

---

##  Project Features & Functions

### 1. Development & Build Pipeline (`-d`)
Using the `--dev` flag switches the project into "High-Speed" mode:
* **Generator:** Uses **Ninja** for lightning-fast incremental compiles.
* **Build Type:** Sets to **Debug**, enabling detailed stack traces and JetBrains/GDB debugger support.
* **Analysis:** Generates `compile_commands.json` for IDE intake and `clang-tidy` linting.

### 2. Automated Testing (`-nt` to skip)
We utilize **QtTest** integrated with **CTest**.
* Tests are located in the `tests/` directory.
* The CI pipeline runs these automatically on every push.
* **Manual Run:** `cd build && ctest --output-on-failure`

### 3. Documentation (`-nd` to skip)
API documentation is extracted from source comments using **Doxygen**.
* **Configuration:** Managed via `doc/Doxygen.in`.
* **Access:** After building, open `doc/html/index.html` in any browser.

## Branching Strategy

| Branch | Prefix | Base From  | Purpose |
| :--- | :--- | :---  | :--- |
| **Feature** | `feature/` | `develop`  | New functionality |

### Workflow
1. **Source:** Always branch from **`develop`** for active work.
2. **Naming:** Use lowercase with hyphens (e.g., `feature/can-parser`).
3. **Merging:** Create a Pull Request (PR) to `develop`.
4. **Stable:** The `main` branch is reserved for verified releases only.

### Naming Convention
- Branch: CBS-[number]-[branchname] , with number from jira
  - example: CBS-4-setup-project
- Pull-Request: CBS-[number] feat|fix|chore: [long description]
  - example: CBS-4 feat: added basic setup

### Issue Tracking
- [Jira](https://pse-can-bus-simulation.atlassian.net/jira/software/projects/KAN/pages)
- [Confluence](https://pse-can-bus-simulation.atlassian.net/wiki/spaces/CA/pages/1015816/Definitionen)

### Additional Information
This project uses the Qt framework (LGPL v3).