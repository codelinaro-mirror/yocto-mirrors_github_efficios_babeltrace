# SPDX-FileCopyrightText: 2025 Philippe Proulx <pproulx@efficios.com>
# SPDX-License-Identifier: MIT

# pyright: strict, reportMissingTypeStubs=false, reportPrivateUsage=false

import os
import sys
import logging
import pathlib

import pytest

try:
    import bt2
    import bt_tests_utils as btu
except ImportError:
    pytest.exit(
        "Cannot import `bt2` or `bt_tests_utils`: make sure to source `tests/utils/env.sh` before you run `bt-pytest`!",
        returncode=1,
    )

_logger = logging.getLogger(__name__)


# Helper functions to access/set dynamic config attributes (satisfies type checker)
def _config_build_root_dir(config: "pytest.Config") -> pathlib.Path:
    return getattr(config, "build_root_dir")


def _set_config_build_root_dir(config: "pytest.Config", path: pathlib.Path) -> None:
    setattr(config, "build_root_dir", path)


def _config_build_tests_dir(config: "pytest.Config") -> pathlib.Path:
    return getattr(config, "build_tests_dir")


def _src_root_dir() -> pathlib.Path:
    return pathlib.Path(__file__).resolve().parent.parent


def _src_tests_dir() -> pathlib.Path:
    return pathlib.Path(__file__).resolve().parent


def _set_config_build_root_tests_dirs(config: "pytest.Config") -> None:
    bt_tests_builddir = os.environ.get("BT_TESTS_BUILDDIR")

    if bt_tests_builddir:
        # `BT_TESTS_BUILDDIR` specifies the `tests` build directory
        _set_config_build_root_dir(
            config, pathlib.Path(bt_tests_builddir).resolve().parent
        )
    else:
        # Default to the root source directory (in-tree build)
        _set_config_build_root_dir(config, _src_root_dir())

    setattr(config, "build_tests_dir", _config_build_root_dir(config) / "tests")


def _log_env_var(name: str) -> None:
    _logger.info(
        "  `{}` environment variable: `{}`".format(name, os.environ.get(name, ""))
    )


def pytest_sessionstart(session: "pytest.Session") -> None:
    _logger.info("pytest_sessionstart():")
    _logger.info("  Root source directory: `{}`".format(_src_root_dir()))
    _logger.info(
        "  Root build directory: `{}`".format(_config_build_root_dir(session.config))
    )
    _logger.info(
        "  `tests` build directory: `{}`".format(
            _config_build_tests_dir(session.config)
        )
    )
    _log_env_var("ASAN_OPTIONS")
    _log_env_var("BABELTRACE_PLUGIN_PATH")
    _log_env_var("BT_TESTS_BUILDDIR")
    _log_env_var("BT_TESTS_CC_BIN")
    _log_env_var("BT_TESTS_PYTHON_BIN")
    _log_env_var("BT_TESTS_PYTHON_CONFIG_BIN")
    _log_env_var("BT_TESTS_SRCDIR")
    _log_env_var("DYLD_LIBRARY_PATH")
    _log_env_var("LD_LIBRARY_PATH")
    _log_env_var("LD_PRELOAD")
    _log_env_var("LIBBABELTRACE2_PLUGIN_PROVIDER_DIR")
    _log_env_var("PATH")
    _logger.info("  `sys.path` value: {}".format(sys.path))
    _logger.info("  `bt2` package version: {}".format(bt2.__version__))


def pytest_configure(config: "pytest.Config") -> None:
    _set_config_build_root_tests_dirs(config)
    setattr(config, "src_tests_dir", _src_tests_dir())
    setattr(config, "ctf_traces_dir", _src_tests_dir() / "data/ctf-traces")


@pytest.fixture(scope="session")
def src_root_dir() -> pathlib.Path:
    return _src_root_dir()


@pytest.fixture(scope="session")
def src_tests_dir() -> pathlib.Path:
    return _src_tests_dir()


@pytest.fixture(scope="session")
def build_root_dir(request: "pytest.FixtureRequest") -> pathlib.Path:
    return _config_build_root_dir(request.config)


@pytest.fixture(scope="session")
def build_tests_dir(request: "pytest.FixtureRequest") -> pathlib.Path:
    return _config_build_tests_dir(request.config)


@pytest.fixture(scope="session")
def data_dir() -> pathlib.Path:
    return _src_tests_dir() / "data"


@pytest.fixture(scope="session")
def ctf_traces_dir(data_dir: pathlib.Path) -> pathlib.Path:
    return data_dir / "ctf-traces"


@pytest.fixture(scope="session")
def muxer_comp_cls() -> bt2._FilterComponentClassConst:
    return bt2.find_plugin(
        "utils"
    ).filter_component_classes[  # pyright: ignore[reportOptionalMemberAccess]
        "muxer"
    ]


@pytest.fixture(scope="session")
def sink_ctf_comp_cls() -> bt2._SinkComponentClassConst:
    return bt2.find_plugin(
        "ctf"
    ).sink_component_classes[  # pyright: ignore[reportOptionalMemberAccess]
        "fs"
    ]


@pytest.fixture(scope="session")
def src_ctf_comp_cls() -> bt2._SourceComponentClassConst:
    return bt2.find_plugin(
        "ctf"
    ).source_component_classes[  # pyright: ignore[reportOptionalMemberAccess]
        "fs"
    ]


@pytest.fixture(scope="session")
def trimmer_comp_cls() -> bt2._FilterComponentClassConst:
    return bt2.find_plugin(
        "utils"
    ).filter_component_classes[  # pyright: ignore[reportOptionalMemberAccess]
        "trimmer"
    ]


@pytest.fixture(scope="session")
def details_comp_cls() -> bt2._SinkComponentClassConst:
    return bt2.find_plugin(
        "text"
    ).sink_component_classes[  # pyright: ignore[reportOptionalMemberAccess]
        "details"
    ]


@pytest.fixture(scope="session")
def pretty_comp_cls() -> bt2._SinkComponentClassConst:
    return bt2.find_plugin(
        "text"
    ).sink_component_classes[  # pyright: ignore[reportOptionalMemberAccess]
        "pretty"
    ]


@pytest.fixture(scope="session")
def dmesg_comp_cls() -> bt2._SourceComponentClassConst:
    return bt2.find_plugin(
        "text"
    ).source_component_classes[  # pyright: ignore[reportOptionalMemberAccess]
        "dmesg"
    ]


@pytest.fixture(scope="session")
def dummy_comp_cls() -> bt2._SinkComponentClassConst:
    return bt2.find_plugin(
        "utils"
    ).sink_component_classes[  # pyright: ignore[reportOptionalMemberAccess]
        "dummy"
    ]


@pytest.fixture(scope="session")
def os_type() -> btu.OsType:
    return btu.os_type()
