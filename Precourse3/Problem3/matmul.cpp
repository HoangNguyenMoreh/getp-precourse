#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

namespace py = pybind11;

// Naive Matrix Multiplication
// C[MxN] = A[MxK] @ B[KxN]
// Do not remove or modify this definitions 
void matmul_c(float* A, float* B, float* C, int M, int N, int K){

  for (int i = 0 ; i < M ; ++i)
  {
    for (int k = 0 ; k < K ; ++k)
    {
      float tmp = A[i * K + k];
      for (int j = 0 ; j < N ; ++j)
      {
        C[i * N + j] += tmp * B[k * N + j];
      }
    }
  }
}

void matmul_c_wrapper(const py::array_t<float>& a, const py::array_t<float>& b, const py::array_t<float>& c, int M, int N, int K){
    auto a_info = a.request();
    auto b_info = b.request();
    auto c_info = c.request();
    matmul_c(static_cast<float*>(a_info.ptr), static_cast<float*>(b_info.ptr), static_cast<float*>(c_info.ptr), M, N, K);
}

PYBIND11_MODULE(matmul_c, m) {
    m.def("matmul_c_interface", &matmul_c_wrapper, "A function that multiply two matrixes");
}
