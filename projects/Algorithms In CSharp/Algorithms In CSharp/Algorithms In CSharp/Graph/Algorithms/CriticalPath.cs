using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Algorithms_In_CSharp.Graph.Algorithms
{
    /// <summary>
    /// 关键路径排序
    /// </summary>
    class CriticalPath
    {
        private List<string> m_criticalPaths;
        // 判断是否是i是否在关键路径上，m_ve[i] == m_vl[i]
        public CriticalPath(IDirectedGraph digraph)
        {
            var topology = new TopologicalAOE(digraph);
            if (!topology.IsDAG())
                throw new ArgumentException("不能获取拓扑排序");
            var ve = topology.GetVE();// m_ve[i] 表示顶点编号i的最早开始时间
            var vl = new int[digraph.V];// 最晚发生
            var topAOEOrder = topology.Order();// 这个最终返回的拓扑排序，但是是从最后一个元素到起点的顺序。
            for (int i = 0; i < vl.Length; ++i)
                vl[i] = ve[digraph.V - 1];//保存为终点的最大的时间
            while(topAOEOrder.Count > 0)
            {
                int v = topAOEOrder.Pop();// 获取检测的点
                foreach(var arc in digraph.GetEdge(v))
                {
                    int w = arc.Other(v);
                    int weight = (int)arc.Weight;
                    if (vl[w] - weight < vl[v])
                        vl[v] = vl[w] - weight;
                }
            }
            m_criticalPaths = new List<string>();
            for (int j = 0; j < digraph.V; ++j)
            {
                foreach (var arc in digraph.GetEdge(j))
                {
                    int w = arc.Other(j);
                    int weight = (int)arc.Weight;
                    int ee = ve[j];
                    int el = vl[w] - weight;// 后继的节点 - 边表示这个活动可以最晚开始的时间
                    char c = (ee == el) ? '*' : '\0';//是否是关键路径。也就是如果最晚开始的时间和最早开始的时间相同。
                    m_criticalPaths.Add($"{j}--{weight}-->{w} {c}");
                }
            }
            
        }

        public List<string> GetCriticalPaths()
        {
            return m_criticalPaths;
        }
        public static void Main()
        {
            var sf = "criticalPath.txt";
            var txr = System.IO.File.OpenText(sf);
            var digrpah = new DirectedWeightedGraph(txr);
            var crt = new CriticalPath(digrpah);
            foreach(var p in crt.GetCriticalPaths())
            {
                Console.WriteLine($"活动：{p}");
            }
        }
    }

    public class TopologicalAOE
    {

        private int[] m_ve; // m_ve[i] 表示时间最晚发生的时间

        private Stack<int> result;
        public TopologicalAOE(IDirectedGraph g)
        {
            DirectedCycle directedCycle = new DirectedCycle(g);
            if (!directedCycle.HasCycle())
            {
                m_ve = new int[g.V];
                //DAG
                solve(g);
            }
        }
        private void solve(IDirectedGraph g)
        {
            // 度的信息
            int count = 0;// 顶点计数
            Stack<int> S = new Stack<int>(), T = new Stack<int>();// 储存入度为0的点，拓扑顶点序列
            Degrees degrees_info = new Degrees(g);
            int[] degrees = new int[g.V];
            for (int i = 0; i < g.V; ++i)
            {
                degrees[i] = degrees_info.InDegree(i);
                if (degrees[i] == 0)
                    S.Push(i);
            }
            while (S.Count > 0)
            {
                int v = S.Pop();
                T.Push(v); // 这个是起始
                ++count;
                foreach (var arc in g.GetEdge(v))
                {
                    // 遍历所有的边
                    int w = arc.Other(v);
                    if (--degrees[w] == 0)
                        S.Push(w);//下一个入点被钦定
                    if (m_ve[v] + arc.Weight > m_ve[w]) // 如果 w 可以尽量晚开始，那就
                        m_ve[w] = m_ve[v] + (int)arc.Weight;
                }
            }
            if (count >= g.V)
            {
                result = T;
            }
        }
        /// <summary>
        /// 返回一个拓扑排序的结果
        /// </summary>
        /// <returns></returns>
        public Stack<int> Order()
        {
            return result;
        }
        public bool IsDAG()
        {
            return result != null;
        }
        /// <summary>
        /// m_ve[i] 表示时间最晚发生的时间
        /// </summary>
        /// <returns></returns>
        public int[] GetVE()
        {
            return m_ve;
        }
    }
}
