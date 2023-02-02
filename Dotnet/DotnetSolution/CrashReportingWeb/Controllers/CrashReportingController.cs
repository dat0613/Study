using Microsoft.AspNetCore.Mvc;
using System.IO.Compression;
using Microsoft.AspNetCore.WebUtilities;
using Microsoft.AspNetCore.Http.Extensions;
using Microsoft.Net.Http.Headers;
using Microsoft.AspNetCore.Http.Features;
using System;

namespace CrashReportingWeb.Controllers
{

    public static class MultipartRequestHelper
    {
        public static string GetBoundary(MediaTypeHeaderValue contentType, int lengthLimit)
        {
            var boundary = HeaderUtilities.RemoveQuotes(contentType.Boundary);
            if (string.IsNullOrWhiteSpace(boundary.Value))
            {
                throw new InvalidDataException("Missing content-type boundary.");
            }

            if (boundary.Length > lengthLimit)
            {
                throw new InvalidDataException(
                    $"Multipart boundary length limit {lengthLimit} exceeded.");
            }

            return boundary.Value;
        }

        public static bool IsMultipartContentType(string contentType)
        {
            return !string.IsNullOrEmpty(contentType)
                   && contentType.IndexOf("multipart/", StringComparison.OrdinalIgnoreCase) >= 0;
        }

        public static bool HasFormDataContentDisposition(ContentDispositionHeaderValue contentDisposition)
        {
            return contentDisposition != null
                   && contentDisposition.DispositionType.Equals("form-data")
                   && string.IsNullOrEmpty(contentDisposition.FileName.Value)
                   && string.IsNullOrEmpty(contentDisposition.FileNameStar.Value);
        }

        public static bool HasFileContentDisposition(ContentDispositionHeaderValue contentDisposition)
        {
            return contentDisposition != null
                   && contentDisposition.DispositionType.Equals("form-data")
                   && (!string.IsNullOrEmpty(contentDisposition.FileName.Value)
                       || !string.IsNullOrEmpty(contentDisposition.FileNameStar.Value));
        }
    }

    [ApiController]
    [Route("[controller]")]
    public class CrashReportingController : ControllerBase
    {
        private static readonly FormOptions _defaultFormOptions = new FormOptions();
        private readonly ILogger<CrashReportingController> _logger;
        private IWebHostEnvironment _hostingEnvironment;

        public CrashReportingController(ILogger<CrashReportingController> logger, IWebHostEnvironment environment)
        {
            _logger = logger;
            _hostingEnvironment = environment;
        }

        [HttpPost]
        [Route("upload/minidump")]
        public async Task<IActionResult> UploadMinidump()
        {
            try
            {
                if (null == Request.ContentType)
                    return BadRequest($"Unknown ContentType");

                if (!MultipartRequestHelper.IsMultipartContentType(Request.ContentType))
                    return BadRequest($"Expected a multipart request, but got {Request.ContentType}");

                using (GZipStream decompressedStream = new GZipStream(Request.Body, CompressionMode.Decompress))
                {
                    MultipartReader reader = new MultipartReader(Request.GetMultipartBoundary(), decompressedStream);
                    MultipartSection section = await reader.ReadNextSectionAsync();

                    while (section != null)
                    {
                        bool hasContentDispositionHeader = ContentDispositionHeaderValue.TryParse(section.ContentDisposition, out var contentDisposition);

                        if (hasContentDispositionHeader)
                        {

                            if (MultipartRequestHelper.HasFileContentDisposition(contentDisposition))
                            {
                                string filePath = @"C:\upload\minidump";
                                string filePathWithName = Path.Combine(filePath, contentDisposition.FileName.Value);
                                Directory.CreateDirectory(filePath);
                                int readBytes = 0;
                                int totalByteRead = 0;
                                byte[] buffer = new byte[1024];

                                using (Stream fileStream = new FileStream(filePathWithName, FileMode.Append, FileAccess.Write))
                                {
                                    do
                                    {
                                        readBytes = await section.Body.ReadAsync(buffer, 0, buffer.Length);
                                        await fileStream.WriteAsync(buffer, 0, readBytes);
                                        totalByteRead += readBytes;
                                    } while (readBytes > 0);
                                }
                            }
                        }

                        section = await reader.ReadNextSectionAsync();
                    }
                }
            }
            catch (Exception ex)
            {// 뭔가 로그를 찍어야 함
                return BadRequest($"Exception!! {ex.Message}");
            }

            return Ok();
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