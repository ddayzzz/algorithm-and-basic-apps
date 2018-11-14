using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Algorithms_In_CSharp.Context
{
    /// <summary>
    /// 线性规划
    /// 来自 算法4 的实现
    /// </summary>
    class LinearProgramming
    {
        private static readonly double EPSILON = 1.0E-10;
        private double[,] a;//tableaux
        private int m;//限制的数量
        private int n;//变量的个数
        private int[] basis;// basis[i] = 变量的关联的行 i

        public LinearProgramming(double[,] A, double[] b, double[] c)
        {
            m = b.Length; n = c.Length;
            for (int i = 0; i < m; ++i)
                if (!(b[i] >= 0))
                    throw new ArgumentException("RHS 必须非负");
            a = new double[m + 1, n + m + 1];
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < n; ++j)
                    a[i, j] = A[i, j];
            for (int i = 0; i < m; ++i)
                a[i, n + i] = 1.0;
            for (int j = 0; j < n; ++j)
                a[m, j] = c[j];
            for (int i = 0; i < m; ++i)
                a[i, m + n] = b[i];
            basis = new int[m];
            for (int i = 0; i < m; ++i)
                basis[i] = n + i;
            Solve();

        }

        private void Solve()
        {
            while (true)
            {

                // find entering column q
                int q = Bland();
                if (q == -1) break;  // optimal

                // find leaving row p
                int p = MinRatioRule(q);
                if (p == -1) throw new ArithmeticException("Linear program is unbounded");

                // pivot
                Pivot(p, q);

                // update basis
                basis[p] = q;
            }
        }
        /// <summary>
        /// 有正数的cost的非基本列的最低的index
        /// </summary>
        /// <returns></returns>
        private int Bland()
        {
            for (int j = 0; j < m + n; ++j)
            {
                if (a[m, j] > 0)
                    return j;
            }
            return -1;//最优的
        }

        private int Dantzig()
        {
            int q = 0;
            for (int j = 1; j < m + n; ++j)
            {
                if (a[m, j] > a[m, q])
                    q = j;
            }
            if (a[m, q] <= 0)
                return -1;//最优
            else
                return q;
        }
        /// <summary>
        /// 找到最小的行p，使用斜率（ratio）最小的原则 
        /// </summary>
        /// <param name="q"></param>
        /// <returns>返回-1表示不存在这个行</returns>
        private int MinRatioRule(int q)
        {
            int p = -1;
            for (int i = 0; i < m; ++i)
            {
                if (a[i, q] <= EPSILON)
                    continue;
                else if (p == -1)
                    p = i;
                else if ((a[i, m + n] / a[i, q]) < (a[p, n + m] / a[p, q]))
                    p = i;
            }
            return p;
        }
        /// <summary>
        /// pivot on entry (p, q) using Gauss-Jordan elimination
        /// </summary>
        /// <param name="p"></param>
        /// <param name="q"></param>
        private void Pivot(int p, int q)
        {
            // 处理行p以及列q
            for (int i = 0; i <= m; ++i)
            {
                for (int j = 0; j <= m + n; ++j)
                {
                    if (i != p && j != q)
                        a[i, j] -= a[p, j] * a[i, q] / a[p, q];
                }
            }
            //zero out column q
            for (int i = 0; i <= m; ++i)
            {
                if (i != p)
                    a[i, q] = 0.0;
            }
            // scale row p
            for (int j = 0; j <= m + n; ++j)
            {
                if (j != q)
                    a[p, j] /= a[p, q];
            }
            a[p, q] = 1.0;
        }
        /// <summary>
        /// Returns the optimal value of this linear program.
        /// </summary>
        /// <returns></returns>
        public double Value()
        {
            return -a[m, m + n];
        }
        /// <summary>
        /// Returns the optimal primal(原始的) solution to this linear program.
        /// </summary>
        /// <returns></returns>
        public double[] Primal()
        {
            double[] x = new double[n];
            for (int i = 0; i < m; i++)
                if (basis[i] < n) x[basis[i]] = a[i, m + n];
            return x;
        }
        /// <summary>
        /// Returns the optimal dual solution to this linear program
        /// </summary>
        /// <returns></returns>
        public double[] Dual()
        {
            double[] y = new double[m];
            for (int i = 0; i < m; i++)
                y[i] = -a[m, n + i];
            return y;
        }
        /// <summary>
        /// is the solution primal feasible?
        /// </summary>
        /// <param name="A"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        private bool IsPrimalFeasible(double[,] A, double[] b)
        {
            double[] x = Primal();

            // check that x >= 0
            for (int j = 0; j < x.Length; j++)
            {
                if (x[j] < 0.0)
                {
                    Console.WriteLine("x[" + j + "] = " + x[j] + " is negative");
                    return false;
                }
            }

            // check that Ax <= b
            for (int i = 0; i < m; i++)
            {
                double sum = 0.0;
                for (int j = 0; j < n; j++)
                {
                    sum += A[i, j] * x[j];
                }
                if (sum > b[i] + EPSILON)
                {
                    Console.WriteLine("not primal feasible");
                    Console.WriteLine("b[" + i + "] = " + b[i] + ", sum = " + sum);
                    return false;
                }
            }
            return true;
        }

        /// <summary>
        /// is the solution dual feasible?
        /// </summary>
        /// <param name="A"></param>
        /// <param name="c"></param>
        /// <returns></returns>
        private bool IsDualFeasible(double[,] A, double[] c)
        {
            double[] y = Dual();

            // check that y >= 0
            for (int i = 0; i < y.Length; i++)
            {
                if (y[i] < 0.0)
                {
                    Console.WriteLine("y[" + i + "] = " + y[i] + " is negative");
                    return false;
                }
            }

            // check that yA >= c
            for (int j = 0; j < n; j++)
            {
                double sum = 0.0;
                for (int i = 0; i < m; i++)
                {
                    sum += A[i, j] * y[i];
                }
                if (sum < c[j] - EPSILON)
                {
                    Console.WriteLine("not dual feasible");
                    Console.WriteLine("c[" + j + "] = " + c[j] + ", sum = " + sum);
                    return false;
                }
            }
            return true;
        }

        /// <summary>
        /// check that optimal value = cx = yb
        /// </summary>
        /// <param name="b"></param>
        /// <param name="c"></param>
        /// <returns></returns>
        private bool IsOptimal(double[] b, double[] c)
        {
            double[] x = Primal();
            double[] y = Dual();
            double value = Value();

            // check that value = cx = yb
            double value1 = 0.0;
            for (int j = 0; j < x.Length; j++)
                value1 += c[j] * x[j];
            double value2 = 0.0;
            for (int i = 0; i < y.Length; i++)
                value2 += y[i] * b[i];
            if (Math.Abs(value - value1) > EPSILON || Math.Abs(value - value2) > EPSILON)
            {
                Console.WriteLine("value = " + value + ", cx = " + value1 + ", yb = " + value2);
                return false;
            }

            return true;
        }

        private static void Test(double[,] A, double[] b, double[] c)
        {
            LinearProgramming lp = new LinearProgramming(A, b, c);
            Console.WriteLine("value = " + lp.Value());
            double[] x = lp.Primal();
            for (int i = 0; i < x.Length; i++)
                Console.WriteLine("x[" + i + "] = " + x[i]);
            double[] y = lp.Dual();
            for (int j = 0; j < y.Length; j++)
                Console.WriteLine("y[" + j + "] = " + y[j]);
        }
        private bool Check(double[,] A, double[] b, double[] c)
        {
            return IsPrimalFeasible(A, b) && IsDualFeasible(A, c) && IsOptimal(b, c);
        }

        /// <summary>
        /// print tableaux
        /// </summary>
        private void Show()
        {
            Console.WriteLine("m = " + m);
            Console.WriteLine("n = " + n);
            for (int i = 0; i <= m; i++)
            {
                for (int j = 0; j <= m + n; j++)
                {
                    Console.WriteLine("{0:0000000.00} ", a[i, j]);
                    // StdOut.printf("%10.7f ", a[i][j]);
                }
                Console.WriteLine();
            }
            Console.WriteLine("value = " + Value());
            for (int i = 0; i < m; i++)
                if (basis[i] < n) Console.WriteLine("x_" + basis[i] + " = " + a[i, m + n]);
            Console.WriteLine();
        }

        private static void Test1()
        {
            double[,] A = {
            { -1,  1,  0 },
            {  1,  4,  0 },
            {  2,  1,  0 },
            {  3, -4,  0 },
            {  0,  0,  1 },
        };
            double[] c = { 1, 1, 1 };
            double[] b = { 5, 45, 27, 24, 4 };
            Test(A, b, c);
        }
        private static void Test2()
        {
            double[,] A = {
            { -1,  1,  0 },
            {  1,  4,  0 },
            {  2,  1,  0 },
            {  3, -4,  0 },
            {  0,  0,  1 },
        };
            double[] c = { 1, 1, 1 };
            double[] b = { 5, 45, 27, 24, 4 };
            Test(A, b, c);
        }
        public static void Main()
        {
            Console.WriteLine("Test1:");
            Test1();

            Console.ReadKey();
        }
    }
}
