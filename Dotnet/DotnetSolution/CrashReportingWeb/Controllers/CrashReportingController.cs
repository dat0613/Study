using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Hosting;
using System.Net.Http;

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
            if (!Request.Body.CanRead || null == Request.QueryString.Value || !Request.QueryString.HasValue)
                return;

            string[] split = Request.QueryString.Value.Split("=");
            if (split.Length < 2)
                return;

            // guid 형식 확인 필요
            string guid = split[1];

            byte[] buffer = new byte[1024];

            string filePath = Path.Combine(@"C:\", @"upload\minidump");
            string filePathWithName = Path.Combine(filePath, guid + ".dmp");
            Directory.CreateDirectory(filePath);

            int totalByteRead = 0;

            using (Stream fileStream = new FileStream(filePathWithName, FileMode.Append, FileAccess.Write))
            {
                while (Request.Body.CanRead)
                {
                    int readLength = await Request.Body.ReadAsync(buffer, 0, buffer.Length);
                    await fileStream.WriteAsync(buffer, 0, readLength);

                    if (readLength < buffer.Length) 
                        break;

                    totalByteRead += readLength;
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