using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Algorithms_In_CSharp.Graph.Algorithms
{
    public class SPCompare
    {
        static string PrintPath(DirectedWeightedGraph g, IShortestPath<DirectedEdge> sp, int startV, int endV)
        {
            StringBuilder sb = new StringBuilder();
            if (endV == startV)
            {
                sb.AppendFormat("{0}->{0} : 0.0", startV);
            }
            else if (!sp.HasPathTo(endV))
            {
                sb.AppendFormat("{0}->{1} : No paths", startV, endV);
            }
            else
            {
                Double len = 0.0;
                foreach (var edge in sp.PathTo(endV))
                {
                    sb.Append(edge.ToString() + ',');
                    len += edge.Weight;
                }
                sb.AppendFormat(" : {0}", len);
            }
            return sb.ToString();
        }
        public static void Main()
        {
            System.IO.TextReader s1 = System.IO.File.OpenText("mediumEWD.txt");
            DirectedWeightedGraph graph1 = new DirectedWeightedGraph(s1);
            System.IO.TextReader s2 = System.IO.File.OpenText("mediumEWD.txt");
            DirectedWeightedGraph graph2 = new DirectedWeightedGraph(s2);
            Console.Write("请输入起点：");
            int st = int.Parse(Console.ReadLine());
            Console.Write("请输入终点：");
            int end = int.Parse(Console.ReadLine());
            // 最小堆优化
            DijkstraSP dijkstraSP = new DijkstraSP(graph1, st);
            // 拓扑排序优化
            AcyclicSP acyclicSP = new AcyclicSP(graph2, st);
            Console.WriteLine("最小堆的结果:\n" + PrintPath(graph1, dijkstraSP, st, end));
            Console.WriteLine("拓扑排序的结果:\n" + PrintPath(graph2, acyclicSP, st, end));
        }
    }
}
