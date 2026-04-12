#include <pybind11/pybind11.h>
#include <pybind11/stl.h>        // auto-converts std::vector <-> Python list
#include <pybind11/operators.h>  // py::self for operator overloads
#include "vec3.h"

namespace py = pybind11;

PYBIND11_MODULE(myvec3, m) {
    m.doc() = "Step 10: C++ Vec3 + Stats library exposed to Python via pybind11";

    // ── Vec3 class ────────────────────────────────────────────────────────────
    py::class_<Vec3>(m, "Vec3",
        "A 3-dimensional vector backed by C++ doubles.")

        .def(py::init<double, double, double>(),
             py::arg("x") = 0.0,
             py::arg("y") = 0.0,
             py::arg("z") = 0.0,
             "Construct a Vec3(x, y, z). All arguments default to 0.")

        // data attributes
        .def_readwrite("x", &Vec3::x, "X component")
        .def_readwrite("y", &Vec3::y, "Y component")
        .def_readwrite("z", &Vec3::z, "Z component")

        // arithmetic operators  (uses py::self from pybind11/operators.h)
        .def(py::self + py::self, "Vector addition")
        .def(py::self - py::self, "Vector subtraction")
        .def(py::self * double(), "Scalar multiplication")
        .def(py::self == py::self, "Equality check")

        // methods
        .def("dot",       &Vec3::dot,       py::arg("other"), "Dot product")
        .def("cross",     &Vec3::cross,     py::arg("other"), "Cross product")
        .def("norm",      &Vec3::norm,      "Euclidean length (magnitude)")
        .def("normalize", &Vec3::normalize, "Return unit vector (raises on zero vector)")
        .def("angle_to",  &Vec3::angle_to,  py::arg("other"),
             "Angle in radians between this and other vector")

        // Python special methods
        .def("__repr__", &Vec3::to_string)
        .def("__str__",  &Vec3::to_string);

    // ── Stats submodule ───────────────────────────────────────────────────────
    py::module_ stats = m.def_submodule("stats",
        "Statistics utilities implemented in C++.");

    stats.def("mean",        &Stats::mean,
              py::arg("data"), "Arithmetic mean of a list of floats");

    stats.def("variance",    &Stats::variance,
              py::arg("data"), "Population variance of a list of floats");

    stats.def("stddev",      &Stats::stddev,
              py::arg("data"), "Population standard deviation");

    stats.def("median",      &Stats::median,
              py::arg("data"), "Median (sorts a copy internally)");

    stats.def("correlation", &Stats::correlation,
              py::arg("x"), py::arg("y"),
              "Pearson correlation coefficient between two equal-length lists");
}
