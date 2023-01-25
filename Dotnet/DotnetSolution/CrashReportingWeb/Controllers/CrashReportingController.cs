using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Hosting;
using System.Net.Http;

using System.Diagnostics;
using System.Net;
using System.Threading.Tasks;
using System.Web;

using System.Threading.Tasks;
using System.IO.Compression;
using Microsoft.AspNetCore.WebUtilities;
using Microsoft.AspNetCore.Http.Extensions;
using Microsoft.Extensions.Primitives;

namespace CrashReportingWeb.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class CrashReportingController : ControllerBase
    {

        private readonly ILogger<CrashReportingController> _logger;
        private IWebHostEnvironment _hostingEnvironment;

        public CrashReportingController(ILogger<CrashReportingController> logger, IWebHostEnvironment environment)
        {
            _logger = logger;
            _hostingEnvironment = environment;
        }

        [HttpPost]
        [Route("upload/minidump")]
        public async void UploadMinidump()
        {
            using (var stream = new GZipStream(Request.Body, CompressionMode.Decompress))
            {
                var reader = new MultipartReader(Request.GetMultipartBoundary(), stream);
                var section = await reader.ReadNextSectionAsync();
                while (section != null)
                {
                    try
                    {
                        byte[] buffer = new byte[1024];

                        string filePath = Path.Combine(@"C:\", @"upload\minidump");
                        string filePathWithName = Path.Combine(filePath, DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss-FFFFFFF") + ".dmp");
                        Directory.CreateDirectory(filePath);

                        int totalByteRead = 0;

                        using (Stream fileStream = new FileStream(filePathWithName, FileMode.Append, FileAccess.Write))
                        {
                            while (true)
                            {
                                int readLength = await section.Body.ReadAsync(buffer, 0, buffer.Length);
                                await fileStream.WriteAsync(buffer);

                                totalByteRead += readLength;

                                if (readLength == 0)
                                    break;
                            }
                        }

                        section = await reader.ReadNextSectionAsync();
                    }
                    catch (ObjectDisposedException e)
                    {
                        break;
                    }
                }
            }
        }

        [HttpPost]
        [Route("upload/symbol")]
        public void UploadSymbol(IFormFile symbolFile)
        {
            if (symbolFile == null || symbolFile.Length <= 0)
                return;
        }
    }
}