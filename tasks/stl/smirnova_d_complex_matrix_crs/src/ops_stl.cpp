// Copyright 2024 Smirnova Daria
#include "stl/smirnova_d_complex_matrix_crs/include/ops_stl.hpp"

#include <algorithm>
#include <complex>
#include <thread>
#include <utility>
#include <vector>

using namespace std::chrono_literals;

// Транспонирование матрицы
smirnova_stl::crs_matrix smirnova_stl::T(const crs_matrix& M) {
  // Создание временной матрицы
  crs_matrix temp_matrix;
  temp_matrix.n_rows = M.n_cols;
  temp_matrix.n_cols = M.n_rows;
  temp_matrix.pointer.assign(temp_matrix.n_rows + 1, 0);
  std::vector<std::vector<std::pair<int, std::complex<double>>>> temp(temp_matrix.n_rows);

  // Заполнение временного хранилища
  for (int i = 0; i < M.n_rows; i++) {
    for (int k = M.pointer[i]; k < M.pointer[i + 1]; k++) {
      int j = M.col_indexes[k];
      temp[j].emplace_back(i, M.non_zero_values[k]);
    }
  }

  // Заполнение временной матрицы из хранилища
  for (int i = 0; i < temp_matrix.n_rows; i++) {
    temp_matrix.pointer[i + 1] = temp_matrix.pointer[i];
    for (auto& j : temp[i]) {
      temp_matrix.col_indexes.push_back(j.first);
      temp_matrix.non_zero_values.push_back(j.second);
      temp_matrix.pointer[i + 1]++;
    }
  }
  // Возврат транспонированной матрицы
  return temp_matrix;
}

// Функция проверки корректности структуры матрицы в формате CRS
bool smirnova_stl::is_crs(const crs_matrix& M) {
  if (M.pointer.size() != size_t(M.n_rows + 1)) return false;
  int non_zero_elems_count = M.non_zero_values.size();
  if (M.col_indexes.size() != size_t(non_zero_elems_count) || M.pointer[M.n_rows] != non_zero_elems_count) return false;
  if (M.pointer[0] != 0) return false;
  for (int i = 1; i <= M.n_rows; i++) {
    if (M.pointer[i] < M.pointer[i - 1]) return false;
  }
  for (int i = 0; i < non_zero_elems_count; i++) {
    if (M.col_indexes[i] < 0 || M.col_indexes[i] >= M.n_cols) return false;
  }
  return true;
}

bool smirnova_stl::StlTestComplexMatrixCrsSeq::pre_processing() {
  internal_order_test();

  *B_M = T(*B_M);
  return true;
}

bool smirnova_stl::StlTestComplexMatrixCrsSeq::validation() {
  internal_order_test();

  if (taskData->inputs.size() != 2 || taskData->outputs.size() != 1 || !taskData->inputs_count.empty() ||
      !taskData->outputs_count.empty())
    return false;
  A_M = reinterpret_cast<crs_matrix*>(taskData->inputs[0]);
  B_M = reinterpret_cast<crs_matrix*>(taskData->inputs[1]);
  Result = reinterpret_cast<crs_matrix*>(taskData->outputs[0]);
  if (A_M == nullptr || B_M == nullptr || Result == nullptr) return false;
  if (!is_crs(*A_M) || !is_crs(*B_M)) return false;
  if (A_M->n_cols != B_M->n_rows) return false;
  return true;
}

// Функция выполнения матричного умножения для последовательного теста
bool smirnova_stl::StlTestComplexMatrixCrsSeq::run() {
  internal_order_test();

  Result->n_rows = A_M->n_rows;
  Result->n_cols = B_M->n_rows;
  Result->pointer.assign(Result->n_rows + 1, 0);
  std::vector<std::vector<std::pair<int, std::complex<double>>>> temp(Result->n_rows);
  for (int i = 0; i < Result->n_rows; i++) {
    for (int j = 0; j < B_M->n_rows; j++) {
      std::complex<double> T;
      for (int k_A = A_M->pointer[i]; k_A < A_M->pointer[i + 1]; k_A++) {
        for (int k_B = B_M->pointer[j]; k_B < B_M->pointer[j + 1]; k_B++) {
          if (A_M->col_indexes[k_A] == B_M->col_indexes[k_B]) {
            T += A_M->non_zero_values[k_A] * B_M->non_zero_values[k_B];
          }
        }
      }
      if (std::abs(T.imag()) > 1e-3 || std::abs(T.real()) > 1e-3) {
        temp[i].emplace_back(j, T);
      }
    }
  }
  for (int i = 0; i < Result->n_rows; i++) {
    Result->pointer[i + 1] = Result->pointer[i];
    for (auto& j : temp[i]) {
      Result->col_indexes.push_back(j.first);
      Result->non_zero_values.push_back(j.second);
      Result->pointer[i + 1]++;
    }
  }
  return true;
}

bool smirnova_stl::StlTestComplexMatrixCrsSeq::post_processing() {
  internal_order_test();

  return true;
}

bool smirnova_stl::StlTestComplexMatrixCrsPar::pre_processing() {
  internal_order_test();

  *B_M = T(*B_M);
  return true;
}

bool smirnova_stl::StlTestComplexMatrixCrsPar::validation() {
  internal_order_test();

  if (taskData->inputs.size() != 2 || taskData->outputs.size() != 1 || !taskData->inputs_count.empty() ||
      !taskData->outputs_count.empty())
    return false;
  A_M = reinterpret_cast<crs_matrix*>(taskData->inputs[0]);
  B_M = reinterpret_cast<crs_matrix*>(taskData->inputs[1]);
  Result = reinterpret_cast<crs_matrix*>(taskData->outputs[0]);
  if (A_M == nullptr || B_M == nullptr || Result == nullptr) return false;
  if (!is_crs(*A_M) || !is_crs(*B_M)) return false;
  if (A_M->n_cols != B_M->n_rows) return false;
  return true;
}

// Функция выполнения матричного умножения для параллельного теста
bool smirnova_stl::StlTestComplexMatrixCrsPar::run() {
  internal_order_test();

  Result->n_rows = A_M->n_rows;
  Result->n_cols = B_M->n_rows;
  Result->pointer.assign(Result->n_rows + 1, 0);
  std::vector<std::vector<std::pair<int, std::complex<double>>>> temp(Result->n_rows);

  int numThreads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads;
  std::mutex temp_mutex;

  auto worker = [&](int start, int end) {
    for (int i = start; i < end; ++i) {
      for (int j = 0; j < B_M->n_rows; ++j) {
        std::complex<double> T;
        for (int k_A = A_M->pointer[i]; k_A < A_M->pointer[i + 1]; ++k_A) {
          for (int k_B = B_M->pointer[j]; k_B < B_M->pointer[j + 1]; ++k_B) {
            if (A_M->col_indexes[k_A] == B_M->col_indexes[k_B]) {
              T += A_M->non_zero_values[k_A] * B_M->non_zero_values[k_B];
            }
          }
        }
        if (std::abs(T.imag()) > 1e-3 || std::abs(T.real()) > 1e-3) {
          std::lock_guard<std::mutex> lock(temp_mutex);
          temp[i].emplace_back(j, T);
        }
      }
    }
  };

  int rowsPerThread = (Result->n_rows + numThreads - 1) / numThreads;
  for (int t = 0; t < numThreads; ++t) {
    int start = t * rowsPerThread;
    int end = std::min(start + rowsPerThread, Result->n_rows);
    if (start < Result->n_rows) {
      threads.emplace_back(worker, start, end);
    }
  }

  for (auto& thread : threads) {
    thread.join();
  }

  for (int i = 0; i < Result->n_rows; ++i) {
    Result->pointer[i + 1] = Result->pointer[i];
    for (auto& j : temp[i]) {
      Result->col_indexes.push_back(j.first);
      Result->non_zero_values.push_back(j.second);
      Result->pointer[i + 1]++;
    }
  }

  return true;
}

bool smirnova_stl::StlTestComplexMatrixCrsPar::post_processing() {
  internal_order_test();

  return true;
}
